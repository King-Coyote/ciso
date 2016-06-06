#include <iostream>
#include <ctime>

#include "Console.hpp"

using namespace std;

void Console::handleEventDebug(EventDebug* ed) {

	time_t t = time(0);
	struct tm * now = localtime(&t);

	std::cout << "DEBUG " << to_string(ed->getLevel()) << ", "
		<< now->tm_mday << "-"
		<< now->tm_mon << "@"
		<< now->tm_hour << ":"
		<< now->tm_min << ":"
		<< now->tm_sec << ": "
		<< ed->getMsg() << endl;

}