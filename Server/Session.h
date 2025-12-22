#include <string>
#include "asio.hpp"
#include <iostream>

class Session : public std::enable_shared_from_this<Session> {
private:
	std::string buffer;
	asio::ip::tcp::socket socket;

public:
	Session(asio::ip::tcp::socket&& socket);
	~Session();

	void start();
	void read();
};