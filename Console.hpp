#pragma once

#include <memory>

#include "EventQueue.hpp"
#include "EventHandler.hpp"

class Console : public EventHandler {

public:

	Console(EventQueue& q);

	void onDebug(std::string msg, int level);

};