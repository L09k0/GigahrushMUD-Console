#include <codecvt>
#include <thread>
#include <fstream>
#include <mutex>
#include <atomic>
#include <deque>

#include "asio.hpp"
#include "Client.h"

#include "nlohmann/json.hpp"

std::string ConvertCP1251ToUTF8(const std::string& str);
std::string ConvertUTF8ToCP1251(const std::string& str);
void JsonParser(const nlohmann::json& json);
std::mutex mtx;
std::string map;

#include "Parser.h"

enum class State { CONNECTED, DISCONNECTED };

std::atomic<bool> running = true;
std::atomic<bool> bgRunning = false;

State state = State::DISCONNECTED;


std::vector<std::string> serverMessages;

std::string ip;
std::string port;
std::string nick;

asio::io_context io_context;
Client client(io_context, ip, port);

std::string lastCommand;

std::thread bg;


std::string ConvertCP1251ToUTF8(const std::string& str)
{
	int len = MultiByteToWideChar(1251, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len];
	MultiByteToWideChar(1251, 0, str.c_str(), -1, wstr, len);

	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, 0, 0);
	char* utf8 = new char[len];
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, 0, 0);

	std::string result(utf8);
	delete[] wstr;
	delete[] utf8;

	return result;
}

std::string ConvertUTF8ToCP1251(const std::string& str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, len);

	len = WideCharToMultiByte(1251, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* cp1251 = new char[len];
	WideCharToMultiByte(1251, 0, wstr, -1, cp1251, len, NULL, NULL);

	std::string result(cp1251);
	delete[] wstr;
	delete[] cp1251;

	return result;
}

void UpdateMsgThread();

void Connect() {
	std::lock_guard<std::mutex> lock(mtx);

	if (state == State::CONNECTED) { return; }

	try {
		client.ip = ip;
		client.port = port;

		client.Connect();
		state = State::CONNECTED;
		bgRunning = true;
		bg = std::thread(UpdateMsgThread);
		client.Send(nick);
	}
	catch (const std::exception& ec) {
		state = State::DISCONNECTED;
	}
}

void SendServ(std::string request) {
	std::lock_guard<std::mutex> lock(mtx);

	try {
		client.Send(request);
	}
	catch (const std::exception& e) {
		return;
	}
}

void UpdateMsgThread() 
{
	while (bgRunning) 
	{
		asio::error_code ec;
		client.recv_buffer_server.resize(4096);
		if (client.socket.is_open()) 
		{
			size_t br = client.socket.read_some(asio::buffer(client.recv_buffer_server), ec);

			if (ec) { continue; }

			client.recv_buffer_server.resize(br);

			std::ofstream file("server_response.log", std::ios::app);
			file << client.recv_buffer_server << "\n";
			file << "\n\n\n";
			file.close();

			try 
			{
				nlohmann::json js = nlohmann::json::parse(client.recv_buffer_server);
				std::ofstream jfile("json_parse.log", std::ios::app);
				jfile << js.dump() << "\n";
				jfile << "\n\n\n";
				jfile.close();
				
				JsonParser(js);
			}
			catch (std::exception& er) 
			{
				std::cout << er.what();
			}
		}
	}
	return;
}

void MainThread() 
{
	std::cout << "IP: ";
	std::getline(std::cin, ip);

	std::cout << "Port: ";
	std::getline(std::cin, port);

	std::cout << "Nick: ";
	std::getline(std::cin, nick);

	//ip = "127.0.0.1";
	//port = "15001";
	//nick = "Logko";

	Connect();

	std::string userCommand;

	bool work = true;
	while (work)
	{
		//std::cout << "> ";
		std::getline(std::cin, userCommand);
		userCommand = ConvertCP1251ToUTF8(userCommand);
		//std::cout << userCommand << "\n";

		if (userCommand == "")
		{
			continue;
		}
		else if (userCommand == "q")
		{
			work = false;
		}
		else if (userCommand == "m")
		{
			std::cout << map << "\n";
			continue;
		}

		SendServ(userCommand);
	}

	return;
}

int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::thread mt(MainThread);

	if (mt.joinable()) {
		mt.join();
	}

	if (bg.joinable()) {
		bg.join();
	}

	return 0;
}
