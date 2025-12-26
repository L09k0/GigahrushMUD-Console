#include <string>
#include "asio.hpp"
#include <iostream>
#include "Game/Game.h"
#include <memory>

class Session : public std::enable_shared_from_this<Session> {
private:
	std::string buffer;
	asio::ip::tcp::socket socket;
	Gigahrush::Game& game;
	std::shared_ptr<Gigahrush::Player> sessionPlayer;

public:
	Session(asio::ip::tcp::socket&& socket);
	~Session();

	void start();
	void read();
	void firstTime();
};