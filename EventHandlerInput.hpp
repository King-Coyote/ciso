#pragma once

#include "EventHandler.hpp"

class EventHandlerInput : public EventHandler {

public:

	void handleEvent(Event* e);

	virtual void handleEventInput(EventInput* ei) = 0;

};