#include <iostream>
#include <locale>

#include "Server.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	asio::io_context io_context;
	Server srv(io_context, 15001);
	srv.async_accept();
	io_context.run();
	return 0;
}