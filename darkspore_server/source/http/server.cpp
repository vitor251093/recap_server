
// Include
#include "server.h"

#include <boost/bind/bind.hpp>
#include <boost/beast/core.hpp>
#include <iostream>

// HTTP
namespace HTTP {
	// Server
	Server::Server(boost::asio::io_context& io_service, const std::string& ip, uint16_t port) :
		mIoService(io_service),
		mAcceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip), port))
	{
		boost::beast::error_code error;
		mAcceptor.set_option(boost::asio::socket_base::reuse_address(true), error);
		if (error) {
			std::cout << error.message() << std::endl;
			return;
		}

		do_accept();
		set_router(nullptr);
	}

	Server::~Server() {

	}

	boost::asio::ip::address Server::get_address() const {
		return mAcceptor.local_endpoint().address();
	}

	uint16_t Server::get_port() const {
		return mAcceptor.local_endpoint().port();
	}

	const std::shared_ptr<Router>& Server::get_router() const {
		return mRouter;
	}

	void Server::set_router(const std::shared_ptr<Router>& router) {
		if (router) {
			mRouter = router;
		} else {
			mRouter = std::make_shared<Router>();
		}
	}

	void Server::do_accept() {
		mAcceptor.async_accept(mIoService,
			boost::beast::bind_front_handler(&Server::handle_accept, this));
	}

	void Server::handle_accept(boost::beast::error_code error, boost::asio::ip::tcp::socket socket) {
		if (!error) {
			std::make_shared<Session>(this, std::move(socket))->start();
			do_accept();
		} else {
			std::cout << error.message() << std::endl;
		}
	}
}
