#include <iostream>
#include <ctime>

#include "Console.hpp"

using namespace std;

Console::Console(EventQueue* q) {
	this->mainQ = q;
	mainQ->registerHandler(this, EventType::DEBUG);
}

void Console::handleEvent(const Event& e) {

	Event e2 = e;
	EventDebug* ed = static_cast<EventDebug*>(&e2);
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