#include <locale>

#include "asio.hpp"
#include "Client.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	//Config

	char ip[] = "localhost";
	char port[] = "15001";

	asio::io_context io_context;

	Client client(io_context, ip, port);
	client.Connect();
	std::cout << "Сервер ответил: " << client.Send("Анус") << std::endl;
	return 0;
}