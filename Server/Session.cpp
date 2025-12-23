#include "Session.h"

Session::Session(asio::ip::tcp::socket&& socket) : socket(std::move(socket)) {
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
				std::cout << "Bytes received: " << bytes_received << std::endl;
				std::cout << "Data: ";
				std::cout << self->buffer << std::endl;
				if (self->buffer == "ХУЙ") {
					std::cout << "ANAL: ";
				}
				std::size_t bt = asio::write(self->socket, asio::buffer(self->buffer.data(), bytes_received));
				self->buffer.resize(256);
				self->read();
			}
		}
	);
}