#pragma once

#include "Observer.hpp"

class ObserverNode {

public:

	ObserverNode* next;
	Observer* observer;

};