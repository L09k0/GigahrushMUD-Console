#include "Session.h"

Session::Session(asio::ip::tcp::socket&& socket) : socket(std::move(socket)), game(Gigahrush::Game::Instance()) {
	std::cout << "User connected!" << std::endl;
	buffer.resize(256);
}

Session::~Session() {
	std::cout << "User disconnected!" << std::endl;
}

void Session::start() {
	read();
}

void Session::read() {
	socket.async_read_some(asio::buffer(buffer),
		[self = shared_from_this()](std::error_code ec, std::size_t bytes_received) {
			if (!ec) {
				self->buffer.resize(bytes_received);
				std::string answer = self->game.ParseCommand();
				std::size_t bt = asio::write(self->socket, asio::buffer(answer));
				self->buffer.resize(256);
				self->read();
			}
		}
	);
}