#pragma once

#include "Event.hpp"

class Observer {

public:

	Observer* next;

	virtual void onNotify(Event* e) = 0;

	Observer() : next(nullptr){};

};