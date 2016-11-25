#include <iostream>
#include <ctime>

#include "Console.hpp"

using namespace std;

Console::Console(EventQueue& q) : mainQ(q) {
	this->mainQ.registerHandler(this, EventType::DEBUG);
}

void Console::handleEvent(std::shared_ptr<Event> e) {

	std::shared_ptr<EventDebug> ed = std::dynamic_pointer_cast<EventDebug>(e);
	if (ed == nullptr) { return; }

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