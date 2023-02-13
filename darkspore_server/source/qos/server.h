
#ifndef _QOS_SERVER_HEADER
#define _QOS_SERVER_HEADER

// Include
#include "network/client.h"

// QoS
namespace QoS {
	// Server
	class Server {
		public:
			Server(boost::asio::io_context& io_service, uint16_t port);
			~Server();

			void try_read();

			void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
			void handle_write(const boost::system::error_code& error);

			uint16_t get_port() const;

		private:
			boost::asio::io_context& mIoService;
			boost::asio::ip::udp::socket mSocket;
			boost::asio::ip::udp::endpoint mRemoteEndpoint;

			DataBuffer mReadBuffer;
			DataBuffer mWriteBuffer;
	};
}

#endif
