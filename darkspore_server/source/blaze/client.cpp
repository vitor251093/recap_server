
// Include
#include "client.h"
#include "component.h"

#include "component/usersessioncomponent.h"

#include "utils/log.h"

#include <boost/bind/bind.hpp>
#include <iostream>

// Blaze
namespace Blaze {
	// Client
	Client::Client(boost::asio::io_context& io_service, boost::asio::ssl::context& context) :
		Network::Client(io_service), mSocket(io_service, context)
	{
		static uint32_t id = 0;
		mId = ++id;
		
		//
		int timeout = -1;

		auto nativeHandle = get_socket().native_handle();
		setsockopt(nativeHandle, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(int));
		setsockopt(nativeHandle, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(int));

		mSocket.set_verify_mode(boost::asio::ssl::verify_none);
		mReadBuffer.resize(10240);
	}

	void Client::start() {
		mSocket.async_handshake(boost::asio::ssl::stream_base::server,
			boost::bind(&Client::handle_handshake, this, boost::asio::placeholders::error));
	}

	void Client::send(MessageType message_type, uint32_t message_id, uint16_t component_id, uint16_t command_id, uint16_t error_code, const DataBuffer& buffer) {
		const auto component = ComponentManager::Get(component_id);
		if (component) {
			bool dontSend = component_id == UserSessionComponent::Id && command_id == 25;
			if (!dontSend) {
				std::cout << utils::timestamp << component->GetName() << "::";
				if (message_type == MessageType::Notification) {
					std::cout << component->GetNotificationPacketName(command_id);
				} else {
					std::cout << component->GetReplyPacketName(command_id);
				}
				std::cout << " sent" << std::endl;
			}
		} else {
			std::cout << utils::timestamp << " sending unknown? (" << component_id << ", " << command_id << ")" << std::endl;
		}

#if 1
		DataBuffer& writeBuffer = mWriteBuffers.emplace_back();

		size_t length = buffer.size();

		writeBuffer.write_u16_be(static_cast<uint16_t>(length));
		writeBuffer.write_u16_be(component_id);
		writeBuffer.write_u16_be(command_id);
		writeBuffer.write_u16_be(error_code);

		uint32_t message = 0;
		message |= static_cast<uint32_t>(message_type) << 28;
		message |= message_id & 0xFFFFF;
		writeBuffer.write_u32_be(message);

		if (length > 0) {
			writeBuffer.insert(buffer);
		}
#else
		size_t length = buffer.size();

		mWriteBuffer.write_u16_be(static_cast<uint16_t>(length));
		mWriteBuffer.write_u16_be(static_cast<uint16_t>(header.component));
		mWriteBuffer.write_u16_be(header.command);
		mWriteBuffer.write_u16_be(header.error_code);

		if (header.message_type != MessageType::Notification) {
			uint32_t message = 0;
			message |= static_cast<uint32_t>(header.message_type) << 28;
			// message |= 0 & 0x3FF;
			message |= header.message_id & 0xFFFFF;
			mWriteBuffer.write_u32_be(message);
		} else {
			mWriteBuffer.write_u16_le(static_cast<uint16_t>(header.message_type) << 4);
			mWriteBuffer.write_u16_be(header.message_id);
		}

		if (length > 0) {
			mWriteBuffer.insert(buffer);
		}
#endif
	}

	void Client::notify(const TDF::Packet& packet, uint16_t component, uint16_t command, ErrorCode error) {
		DataBuffer buffer;
		packet.Write(buffer);

		send(MessageType::Notification, 0, component, command, static_cast<uint32_t>(error) >> 16, buffer);
	}

	void Client::reply(const Request& request, ErrorCode error) {
		MessageType messageType = (error != ErrorCode::NONE) ? MessageType::ErrorReply : MessageType::Reply;

		DataBuffer emptyBuffer;
		send(messageType, request.mMessageId, request.mComponent, request.mCommand, static_cast<uint32_t>(error) >> 16, emptyBuffer);
	}

	void Client::reply(const Request& request, const TDF::Packet& packet, ErrorCode error) {
		MessageType messageType = (error != ErrorCode::NONE) ? MessageType::ErrorReply : MessageType::Reply;

		DataBuffer buffer;
		packet.Write(buffer);

		send(messageType, request.mMessageId, request.mComponent, request.mCommand, static_cast<uint32_t>(error) >> 16, buffer);
	}

	void Client::handle_handshake(const boost::system::error_code& error) {
		if (!error) {
			mSocket.async_read_some(boost::asio::buffer(mReadBuffer.data(), mReadBuffer.capacity()),
				boost::bind(&Client::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		} else if (error == boost::asio::error::eof || error == boost::asio::error::connection_reset) {
			std::cout << "Handshake error: Client disconnected." << std::endl;
			delete this;
		} else {
			std::cout << "Handshake error: " << error.message() << std::endl;
			delete this;
		}
	}

	void Client::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
		if (!error) {
			mReadBuffer.resize(bytes_transferred);
			mReadBuffer.set_position(0);

			mWriteBuffers.clear();
			while (mReadBuffer.position() < bytes_transferred) {
				parse_packets();
			}

#if 1
			try {
				for (const auto& buffer : mWriteBuffers) {
					boost::asio::write(mSocket, boost::asio::buffer(buffer.data(), buffer.size()));
				}

				mSocket.async_read_some(boost::asio::buffer(mReadBuffer.data(), mReadBuffer.capacity()),
					boost::bind(&Client::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
			} catch (std::exception&) {
				// Just drop connection?
				delete this;
			}
#else
			boost::asio::async_write(mSocket,
				boost::asio::buffer(mWriteBuffer.data(), mWriteBuffer.size()),
				boost::bind(&Client::handle_write, this, boost::asio::placeholders::error));
#endif
		} else if (error == boost::asio::error::eof || error == boost::asio::error::connection_reset) {
			std::cout << "Error: Client disconnected." << std::endl;
			delete this;
		} else {
			std::cout << "Error: " << error.message() << std::endl;
			delete this;
		}
	}

	void Client::handle_write(const boost::system::error_code& error) {
		if (!error) {
			mWriteBuffer.clear();
			mSocket.async_read_some(boost::asio::buffer(mReadBuffer.data(), mReadBuffer.capacity()),
				boost::bind(&Client::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		} else if (error == boost::asio::error::eof || error == boost::asio::error::connection_reset) {
			std::cout << "Error: Client disconnected." << std::endl;
			delete this;
		} else {
			std::cout << "Error: " << error.message() << std::endl;
			delete this;
		}
	}

	void Client::parse_packets() {
		/*
		uint32_t message = mReadBuffer.read_u32_be();
		header.message_type = static_cast<Blaze::MessageType>(message >> 30);
		header.message_id = message & 0x3FFFFFF;
		*/

		Request request(*this);
		request.mLength = mReadBuffer.read_u16_be();
		request.mComponent = mReadBuffer.read_u16_be();
		request.mCommand = mReadBuffer.read_u16_be();
		request.mErrorCode = mReadBuffer.read_u16_be();

		uint32_t message = mReadBuffer.read_u32_be();
		request.mMessageType = static_cast<MessageType>(message >> 28);
		request.mMessageId = message & 0xFFFFF;
		/* As far as I can tell darkspore limits blaze packets to 0xFFFF bytes
		if (message & 1) {
			request.mLength |= mReadBuffer.read_u16_be();
		}
		*/
		mParser.Read(mReadBuffer);

		const auto component = ComponentManager::Get(request.mComponent);
		if (!component) {
			std::cout << "Unknown component: " << request.mComponent << std::endl;
			return;
		}

		if (component->ParsePacket(request)) {
			bool dontSend = request.mComponent == UserSessionComponent::Id && request.mCommand == 25;
			if (!dontSend) {
				std::cout << utils::timestamp << component->GetName() << "::" << component->GetReplyPacketName(request.mCommand) << " received" << std::endl;
				Log(get_request());
				std::cout << std::endl;
			}
		} else {
			std::cout << utils::timestamp << component->GetName() << ": Command " << request.mCommand << " does not exist." << std::endl;
		}
	}

	// Request
	Request::Request(Client& client)
		: mClient(client) {}

	void Request::notify(const TDF::Packet& packet, uint16_t component, uint16_t command, ErrorCode error) const {
		mClient.notify(packet, component, command, error);
	}

	void Request::reply(ErrorCode error) const {
		mClient.reply(*this, error);
	}

	void Request::reply(const TDF::Packet& packet, ErrorCode error) const {
		mClient.reply(*this, packet, error);
	}
}

/*
	Encoded names in client
		ADDR - union
		NQOS
		NLMP
		BSDK - string
		BTIM - string
		CLNT - string
		CSKU - string
		CVER - string
		DSDK - string
		ENV - string
		FPID - union
		LOC - integer
		NAME - string
		PLAT - string
		PROF - string
		TIID - unknown
		RPRT - unknown
		PJID - unknown
		OIDS - unknown
		CSIG - unknown
		ADRS - unknown
		XDNS - integer
		SECU - integer
		MSGS - unknown
		NMAP - unknown
		AMAP - unknown
*/
