#pragma once

#include "EventHandler.hpp"
#include "EventQueue.hpp"

class Console : public EventHandler {

private:

	EventQueue* mainQ;

public:

	Console(EventQueue* q);

	void handleEvent(const Event& e);

};