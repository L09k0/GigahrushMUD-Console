#include <string>
#include "asio.hpp"
#include <iostream>
#include "Game/Game.h"

class Session : public std::enable_shared_from_this<Session> {
private:
	std::string buffer;
	asio::ip::tcp::socket socket;
	Gigahrush::Game& game;

public:
	Session(asio::ip::tcp::socket&& socket);
	~Session();

	void start();
	void read();
};