#pragma once

#include "Event.hpp"

class EventHandler {

public:

	virtual ~EventHandler() {};

	virtual void handleEvent(const Event& e) = 0;

};