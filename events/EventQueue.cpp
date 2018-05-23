#include <algorithm>
#include <iostream>

#include "EventQueue.hpp"

using namespace std;

namespace ci {

void EventQueue::processEvent(const Event& e) {

	for (auto eh : this->eventHandlerVectorMap[e.type]) {
		eh->handleEvent(e);
	}

}

void EventQueue::registerHandler(EventHandler& handler, EventType type) {

	// if the type vector doesn't exist yet, create it.
	if (this->eventHandlerVectorMap.count(type) == 0) {
		this->eventHandlerVectorMap[type] = vector<EventHandler*>();
	}

	for (auto eh : this->eventHandlerVectorMap[type]) {
		if (eh == &handler) {
			// this handler is already registered as a listener, return
			return;
		}
	}
	
	this->eventHandlerVectorMap[type].push_back(&handler);
	return;

}
void EventQueue::deregisterHandler(EventHandler& handler, EventType type) {

	int i = 0;
	for (auto eh : this->eventHandlerVectorMap[type]) {
		if (eh == &handler) {
			// below lines swap the current handler with the one at the back, then pop the back.
			// this operation is O(1), faster than reomving and re-sorting the vector.
			std::swap(this->eventHandlerVectorMap[type][i], this->eventHandlerVectorMap[type].back());
			this->eventHandlerVectorMap[type].pop_back();
			// must return here, otherwise the iterator is invalid and will throw an error.
			return;
		}
		i++;
	}

}

void EventQueue::postEvent(const Event& e) {
	this->events.push(Event(e));
}

void EventQueue::processEvents() {
	while (this->events.empty() == false) {
		processEvent(this->events.front());
		this->events.pop();
	}
}

}