#include "asio.hpp"
#include "Client.h"

int main()
{
	//Config

	char ip[] = "localhost";
	char port[] = "15001";

	asio::io_context io_context;

	Client client(io_context, ip, port);
	client.Connect();

	while (true) {
		std::string msg;
		std::getline(std::cin, msg);
		std::cout << "Сервер ответил: " << client.Send(msg) << std::endl;
	}
	return 0;
}