#include <locale>
#include <codecvt>
#include <thread>
#include <mutex>
#include <atomic>

#include "asio.hpp"
#include "Client.h"

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

std::atomic<bool> running = true;
bool first = true;

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

std::string ServerAnswer(std::string request) {
	std::string res = "Типо ответ от сервера";

	return res;
}

int main()
{
	//FTXUI
	std::string test;

	ftxui::Component vvod1 = ftxui::Input(&test);

	std::vector<std::string> testLog;

	auto vvod1Handler = ftxui::CatchEvent(vvod1, [&](ftxui::Event event) {

		if (event == ftxui::Event::Return) {
			testLog.push_back(ServerAnswer(test));
			test = "";
			return true;
		}

		return false;

		});

	ftxui::Component inputPole = ftxui::Container::Vertical({
			vvod1Handler
		});

	auto renderer = ftxui::Renderer(inputPole, [&] {
		//Logs
		
		std::vector<ftxui::Element> logItems;
		ftxui::Element logWindow = ftxui::vbox();

		for (const auto& it : testLog) {
			logItems.push_back(ftxui::text(it));
		}

		logWindow = ftxui::vbox(logItems);

		return ftxui::vbox({
			ftxui::text("MUD") | ftxui::bold,
			logWindow | ftxui::border,
			ftxui::hbox(ftxui::text("Команда"), vvod1->Render())}) | ftxui::border;
		});

	auto screen = ftxui::ScreenInteractive::TerminalOutput();
	screen.Loop(renderer);
	//EFTXUI

	#ifdef _WIN32
		SetConsoleCP(1251); 
		SetConsoleOutputCP(1251);
	#else
		setlocale(LC_ALL, "ru_RU.UTF-8");
	#endif
	//Config

	std::string ip;
	std::string port;

	std::cout << "Введите IP: ";
	std::getline(std::cin, ip);
	std::cout << "Введите порт: ";
	std::getline(std::cin, port);

	//audiere::AudioDevicePtr device = audiere::OpenDevice();
	//audiere::SoundEffect* sound = audiere::OpenSoundEffect(device, "effect.mp3", audiere::SINGLE);

	std::string nick;
	do {
		std::cout << "Введите ник: \n> ";
		std::getline(std::cin, nick);
	} while (nick == "");

	while (running) {
		asio::io_context io_context;
		//sound->play();
		try {
			Client client(io_context, ip, port);
			client.Connect();

			std::string nickConv = ConvertCP1251ToUTF8(nick);
			std::string str = client.Send(nickConv);
			std::string response_local = ConvertUTF8ToCP1251(str);
			std::cout << response_local << std::endl;

			while (true) {
				try {
					std::cout << "> ";
					std::string msg;
					std::getline(std::cin, msg);
					if (msg == "") continue;
					if (msg == "exit") { running = false; break; };

					std::string msg_utf8 = ConvertCP1251ToUTF8(msg);
					std::string str = client.Send(msg_utf8);
					std::string response_local = ConvertUTF8ToCP1251(str);
					std::cout << response_local << std::endl;
				}
				catch (const std::exception& e) {
					std::cout << "Ошибка соединения подключится.\nПопробовать снова? (Y/N) :";
					std::string ans;
					std::getline(std::cin, ans);
					if (ans == "Y" || ans == "y") {
						client.Connect();
					}
					else {
						running = false;
						break;
					}
				}
			}
		}
		catch (const std::exception& e) {
			std::cout << "Невозможно подключится.\nПопробовать снова? (Y/N) :";
			std::string ans;
			std::getline(std::cin, ans);
			if (ans == "Y" || ans == "y") {
				continue;
			}
			else {
				running = false;
			}
		}
	}
	return 0;
}