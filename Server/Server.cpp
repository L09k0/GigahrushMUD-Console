#include "Session.h"
#include "Server.h"

Server::Server(asio::io_context& io_context, std::uint16_t port) :
	io_context(io_context),
	acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {}

void Server::async_accept() {
	socket.emplace(io_context);

	acceptor.async_accept(*socket, [&](asio::error_code error) {
		std::make_shared<Session>(std::move(*socket))->start();
		async_accept();
		});
}
