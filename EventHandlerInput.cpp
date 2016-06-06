#include <iostream>
#include <string>

#include "EventHandlerInput.hpp"

void EventHandlerInput::handleEvent(Event* e) {

	EventInput* ie = static_cast<EventInput*>(e);

	this->handleEventInput(ie);

}