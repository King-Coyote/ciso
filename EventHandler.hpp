#pragma once

#include <memory>

#include "Event.hpp"

class EventHandler {

public:

	virtual ~EventHandler() {};

	virtual void handleEvent(std::shared_ptr<Event> e) = 0;

};