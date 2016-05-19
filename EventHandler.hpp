#pragma once

#include "Event.hpp"

class EventHandler {

public:

	virtual void handleEvent(Event* e) = 0;

};