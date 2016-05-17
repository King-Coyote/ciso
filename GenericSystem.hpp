#pragma once

#include <string>

#include "Observer.hpp"
#include "Subject.hpp"
#include "Event.hpp"

class GenericSystem : public Observer, public Subject {

public:

	std::string name;

	void onNotify(Event* e);

	GenericSystem(std::string name) : name(name) {};

};