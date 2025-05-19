
// Include
#include "server.h"

#include <boost/bind/bind.hpp>
#include <iostream>
#include <ctime>
#include <iomanip>

// QoS
namespace QoS {
	// Server
	Server::Server(boost::asio::io_context& io_service, boost::asio::ip::address ip, uint16_t port)
		: mIoService(io_service), mSocket(mIoService, boost::asio::ip::udp::endpoint(ip, port))
	{
		mReadBuffer.resize(10240);
		try_read();
	}

	Server::~Server() {
		// Empty
	}

	void Server::try_read() {
		mSocket.async_receive_from(
			boost::asio::buffer(mReadBuffer.data(), mReadBuffer.capacity()), mRemoteEndpoint,
			boost::bind(&Server::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
		);
	}

	void Server::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
		if (!error) {
			mReadBuffer.resize(bytes_transferred);
			mReadBuffer.set_position(0);

			uint32_t id = mReadBuffer.read_u32_be();
			uint32_t version = mReadBuffer.read_u32_be();

			mWriteBuffer.clear();
			if (version == 1) {
				uint32_t requestSecret = mReadBuffer.read_u32_be();
				uint32_t requestId = mReadBuffer.read_u32_be();
				uint32_t ticks = mReadBuffer.read_u32_be();

				auto tp = std::chrono::time_point<std::chrono::system_clock>(std::chrono::milliseconds(ticks));
				auto t = std::chrono::system_clock::to_time_t(tp);

			if (Application::IsVerboseTimestamps()) {
				std::cout << "QoS(" << bytes_transferred << "): ";
				std::cout << "id(" << id << "); ";
				std::cout << "request_secret(" << requestSecret << "); ";
				std::cout << "unk2(" << requestId << "); ";
				std::cout << "version(" << version << "); ";
				std::cout << "timestamp(" << std::put_time(std::localtime(&t), "%T") << ");";
				std::cout << std::endl;
			}

				mWriteBuffer.write_u32_be(id);
				mWriteBuffer.write_u32_be(version);
				mWriteBuffer.write_u32_be(requestSecret);
				mWriteBuffer.write_u32_be(requestId);
				mWriteBuffer.write_u32_be(ticks);

				mWriteBuffer.write_u32_be(mRemoteEndpoint.address().to_v4().to_uint()); // offset: 0x130
				mWriteBuffer.write_u16_be(mRemoteEndpoint.port()); // offset: 0x12E

				mWriteBuffer.write_u32_be(0x12345678);
			} else if (version == 2) {
				std::cout << "QoS(" << bytes_transferred << "): ";
				std::cout << "id(" << id << "); ";
				std::cout << "version(" << version << "); ";
				std::cout << std::endl;

				mWriteBuffer.write_u32_be(id);
				mWriteBuffer.write_u32_be(version);
				mWriteBuffer.write_u32_be(0x1337); // still has to be request secret
				mWriteBuffer.write_u32_be(2); // probe id
				mWriteBuffer.write_u32_be(0);

				mWriteBuffer.write_u32_be(2); // offset: 0x120
				mWriteBuffer.write_u32_be(0xDEAD);
				mWriteBuffer.write_u32_be(2); // current probe id? (max = probeCount)
				mWriteBuffer.write_u32_be(0xBEEF);
				mWriteBuffer.write_u32_be(2); // current probe id? (max = probeCount)
				mWriteBuffer.write_u32_be(0x8925);
			}

			if (mWriteBuffer.size() > 0) {
				mSocket.async_send_to(
					boost::asio::buffer(mWriteBuffer.data(), mWriteBuffer.capacity()), mRemoteEndpoint,
					boost::bind(&Server::handle_write, this, boost::asio::placeholders::error)
				);
			}
		} else if (error == boost::asio::error::eof || error == boost::asio::error::connection_reset) {
			std::cout << "Error: Client disconnected." << std::endl;
		} else {
			std::cout << "Error: " << error.message() << std::endl;
		}

		try_read();
	}

	void Server::handle_write(const boost::system::error_code& error) {
		if (!error) {
			//
		} else if (error == boost::asio::error::eof || error == boost::asio::error::connection_reset) {
			std::cout << "Error: Client disconnected." << std::endl;
		} else {
			std::cout << "Error: " << error.message() << std::endl;
		}
	}

	boost::asio::ip::address Server::get_address() const {
		return mSocket.local_endpoint().address();
	}

	uint16_t Server::get_port() const {
		return mSocket.local_endpoint().port();
	}
}
