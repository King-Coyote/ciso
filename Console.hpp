#pragma once

#include <memory>

#include "EventHandler.hpp"
#include "EventQueue.hpp"

class Console : public EventHandler {

public:

	Console(EventQueue& q);

	void onDebug(std::string msg, int level);

};