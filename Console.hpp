#pragma once

#include "EventHandlerDebug.hpp"

class Console : public EventHandlerDebug {

public:

	Console() {};

	void handleEventDebug(EventDebug* ed);

};