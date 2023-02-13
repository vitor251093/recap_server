
#ifndef _BLAZE_CLIENT_HEADER
#define _BLAZE_CLIENT_HEADER

// Include
#include "types.h"
#include "functions.h"

#include "network/client.h"

#include "sporenet/user.h"

#include <boost/asio/ssl.hpp>

// Blaze
namespace Blaze {
	class Request;

	// Client
	class Client : public Network::Client {
		public:
			Client(boost::asio::io_context& io_service, boost::asio::ssl::context& context);

			auto& get_socket() { return mSocket.lowest_layer(); }

			auto get_id() const { return mId; }

			const SporeNet::UserPtr& get_user() const { return mUser; }
			void set_user(const SporeNet::UserPtr& user) { mUser = user; }

			const auto& get_request() const { return mParser.GetDocument(); }

			auto& data() { return mData; }
			const auto& data() const { return mData; }

			void start();

			void notify(const TDF::Packet& packet, uint16_t component, uint16_t command, ErrorCode error = ErrorCode::NONE);
			void reply(const Request& request, ErrorCode error = ErrorCode::NONE);
			void reply(const Request& request, const TDF::Packet& packet, ErrorCode error = ErrorCode::NONE);

			void handle_handshake(const boost::system::error_code& error);
			void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
			void handle_write(const boost::system::error_code& error);

		private:
			void send(MessageType message_type, uint32_t message_id, uint16_t component_id, uint16_t command_id, uint16_t error_code, const DataBuffer& buffer);

			void parse_packets();

		protected:
			boost::asio::ssl::stream<boost::asio::ip::tcp::socket> mSocket;

			TDF::Parser mParser;

			std::vector<DataBuffer> mWriteBuffers;

			SporeNet::UserPtr mUser;

			ClientData mData;
			
			uint32_t mCurrentMessageId;
			uint32_t mId;
	};

	// Request
	class Request {
		public:
			Request(Client& client);

			const auto& get_request() const { return mClient.get_request(); }

			auto& get_client() { return mClient; }
			const auto& get_client() const { return mClient; }

			decltype(auto) get_user() const { return mClient.get_user(); }
			void set_user(const SporeNet::UserPtr& user) { mClient.set_user(user); }

			auto get_component() const { return mComponent; }
			auto get_command() const { return mCommand; }

			decltype(auto) begin() const { return get_request().MemberBegin(); }
			decltype(auto) end() const { return get_request().MemberEnd(); }
			decltype(auto) find(const std::string& field) const { return get_request().FindMember(field); }
			decltype(auto) operator[](const std::string& field) const { return get_request()[field]; }

			void notify(const TDF::Packet& packet, uint16_t component, uint16_t command, ErrorCode error = ErrorCode::NONE) const;
			void reply(ErrorCode error = ErrorCode::NONE) const;
			void reply(const TDF::Packet& packet, ErrorCode error = ErrorCode::NONE) const;

		private:
			Client& mClient;

			MessageType mMessageType = MessageType::Message;
			uint32_t mMessageId = 0;

			uint16_t mLength = 0;
			uint16_t mComponent = 0;
			uint16_t mCommand = 0;
			uint16_t mErrorCode = 0;
			
			friend class Client;
	};
}

#endif
