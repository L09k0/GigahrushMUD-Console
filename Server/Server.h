#include <optional>
#include "asio.hpp"

class Server {
	private:
		asio::io_context& io_context;
		asio::ip::tcp::acceptor acceptor;
		std::optional<asio::ip::tcp::socket> socket;

	public:
		Server(asio::io_context& io_context, std::uint16_t port);
		void async_accept();
};