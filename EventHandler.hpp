#pragma once

#include "Event.hpp"

class EventHandler {

public:

	virtual ~EventHandler() {};

	virtual void handleEvent(Event* e) = 0;

};