#include <algorithm>

#include "EventQueue.hpp"

void EventQueue::processEvent(const Event& e) {

	for (EventHandler* eh : this->vectorMap[e.type]) {
		eh->handleEvent(e);
	}

}

void EventQueue::registerHandler(EventHandler* handler, EventType type) {

	// if the type vector doesn't exist yet, create it.
	if (this->vectorMap.count(type) == 0) {
		this->vectorMap[type] = *(new std::vector<EventHandler*>());
	}

	for (EventHandler* eh : this->vectorMap[type]) {
		if (eh == handler) {
			// this handler is already registered as a listener, return
			return;
		}
	}

	this->vectorMap[type].push_back(handler);
	return;

}

void EventQueue::deregisterHandler(EventHandler* handler, EventType type) {

	int i = 0;
	for (EventHandler* eh : this->vectorMap[type]) {
		if (eh == handler) {
			// below lines swap the current handler with the one at the back, then pop the back.
			// this operation is O(1), faster than reomving and re-sorting the vector.
			std::swap(this->vectorMap[type][i], this->vectorMap[type].back());
			this->vectorMap[type].pop_back();
			// must return here, otherwise the iterator is invalid and will throw an error.
			return;
		}
		i++;
	}

}

void EventQueue::postEvent(const Event& e) {

	this->eventStream.push(e);

}

void EventQueue::processEvents() {

	while (this->eventStream.empty() == false) {
		processEvent(this->eventStream.front());
		this->eventStream.pop();
	}

}
/*
EventQueue& EventQueue::getGlobal() {

	static EventQueue g();

	return g;
	
}
*/
EventQueue::~EventQueue() {



}