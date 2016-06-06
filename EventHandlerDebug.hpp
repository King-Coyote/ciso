#pragma once

#include "EventHandler.hpp"

class EventHandlerDebug : public EventHandler {


public:

	void handleEvent(Event* e);

	virtual void handleEventDebug(EventDebug* ed) = 0;

};