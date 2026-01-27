#include "Client.h"

Client::Client(asio::io_context& io_context_, std::string ip, std::string port) :
	io_context(io_context_),
	socket(io_context),
	resolver(io_context),
	ip(ip),
	port(port) {}

void Client::Connect() 
{
	asio::connect(socket, resolver.resolve(ip, port));
}

Client::~Client() 
{
	if (socket.is_open()) 
	{
		socket.shutdown(asio::ip::tcp::socket::shutdown_both);
		socket.close();
	}
}

void Client::Send(std::string& data) 
{
	try
	{
		std::size_t bytes_transmited = asio::write(socket, asio::buffer(data));
	}
	catch (const std::exception& e)
	{
		std::cout << "Ошибка отправки данных\n" << e.what() << "\n";
	}
}


