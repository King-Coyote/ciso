#include "EventHandlerDebug.hpp"

#include <iostream>

void EventHandlerDebug::handleEvent(Event* e) {

	EventDebug* ed = static_cast<EventDebug*>(e);
	if (ed == nullptr) { return; }

	this->handleEventDebug(ed);

}