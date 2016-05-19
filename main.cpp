#include <SFML/Graphics.hpp>
#include <iostream>
//TEMPORARY
#include <vector>
#include <string>

#include "GenericSystem.hpp"
#include "Event.hpp"
#include "EventQueue.hpp"
#include "EventHandlerDebug.hpp"

int main() {

	/*
	std::unordered_map<int, Event*> derp;

	Event* fuckShitBitchCunt = new Event();
	Event* event2 = new Event();

	std::cout << std::to_string(derp.count(0));
	derp[0] = fuckShitBitchCunt;
	std::cout << "\n" << std::to_string(derp.count(0));
	derp[0] = nullptr;
	std::cout << "\n" << std::to_string(derp.count(0));
	derp[1] = event2;
	derp.erase(0);
	std::cout << "\n" << std::to_string(derp.count(1));
	*/

	EventQueue* q = new EventQueue(1000);

	EventHandlerDebug* handle1 = new EventHandlerDebug();
	EventHandlerDebug* handle2 = new EventHandlerDebug();
	EventHandlerDebug* handle3 = new EventHandlerDebug();

	q->registerHandler(handle1, EventType::DEBUG);
	q->registerHandler(handle2, EventType::DEBUG);
	q->registerHandler(handle3, EventType::DEBUG);

	EventDebug* dummyEvent = new EventDebug();

	q->postEvent(dummyEvent);
	q->processEvents();

	q->deregisterHandler(handle2, EventType::DEBUG);

	q->postEvent(dummyEvent);
	q->processEvents();

	while (true) {
	}
	
	return 0;

}