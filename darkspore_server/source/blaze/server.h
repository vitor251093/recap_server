
#ifndef _BLAZE_SERVER_HEADER
#define _BLAZE_SERVER_HEADER

// Include
#include "client.h"

// Blaze
namespace Blaze {
	constexpr size_t BUFFER_SIZE = 10240;

	// Server
	class Server {
		public:
			Server(boost::asio::io_context& io_service, const std::string& ip, uint16_t port);
			~Server();

			void handle_accept(Client* client, const boost::system::error_code& error);

			boost::asio::ip::address get_address() const;
			uint16_t get_port() const;

		private:
			static bool verify_callback(bool preverified, boost::asio::ssl::verify_context& context);

		private:
			boost::asio::io_context& mIoService;
			boost::asio::ip::tcp::acceptor mAcceptor;
			boost::asio::ssl::context mContext;
	};
}

#endif
