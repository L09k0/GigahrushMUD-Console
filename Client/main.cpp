#include <locale>

#include "asio.hpp"
#include "Client.h"

int main()
{
	#ifdef _WIN32
		SetConsoleCP(CP_UTF8); 
		SetConsoleOutputCP(CP_UTF8);
		system("chcp 65001 >nul");
	#else
		setlocale(LC_ALL, "ru_RU.UTF-8");
	#endif
	setlocale(LC_ALL, "ru_RU.UTF-8");
	//Config

	char ip[] = "localhost";
	char port[] = "15001";

	asio::io_context io_context;

	Client client(io_context, ip, port);
	client.Connect();

	while (true) {
		std::cout << "> ";
		std::string msg;
		std::getline(std::cin, msg);
		if (msg == "") continue;
		//std::cout << msg;

		std::cout << "Сервер ответил: ";
		std::string str = client.Send(msg);
		std::cout << str << std::endl;
	}
	return 0;
}