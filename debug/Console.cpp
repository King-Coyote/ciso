#include <iostream>
#include <ctime>

#include "Console.hpp"

using namespace std;

Console::Console(EventQueue& q) :
	EventHandler(q, { EventType::DEBUG })
{}

void Console::onDebug(std::string msg, int level) {
	time_t t = time(0);
	struct tm * now = localtime(&t);

	std::cout << "DEBUG " << to_string(level) << ", "
		<< now->tm_mday << "-"
		<< now->tm_mon << "@"
		<< now->tm_hour << ":"
		<< now->tm_min << ":"
		<< now->tm_sec << ": "
		<< msg << endl;
}