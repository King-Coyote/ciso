#pragma once

#include "ObserverNode.hpp"
#include "Event.hpp"

class Subject {

public:

	Observer* head;

	void addObserver(Observer* observer);

	void removeObserver(Observer* observer);

	void notifyObservers(Event* e);

	Subject() : head(nullptr){};

};