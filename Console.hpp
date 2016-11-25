#pragma once

#include <memory>

#include "EventHandler.hpp"
#include "EventQueue.hpp"

class Console : public EventHandler {

private:

	EventQueue& mainQ;

public:

	Console(EventQueue& q);

	void handleEvent(std::shared_ptr<Event> e);

};