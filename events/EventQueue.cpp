#include <algorithm>
#include <iostream>

#include "EventQueue.hpp"

using namespace std;

namespace ci {

unique_ptr<EventQueue> EventQueue::instance = nullptr;

EventQueue* EventQueue::getInstance() {
	if (!EventQueue::instance.get()) {
		EventQueue::instance.reset(new EventQueue());
	}
	return EventQueue::instance.get();
}

void EventQueue::processEvent(Event* e) {

	for (auto& eh : this->eventHandlerVectorMap[e->getType()]) {
		eh->handleEvent(e);
	}

}

void EventQueue::registerHandler(EventReceivingKey&& k, EventHandler& handler, EventType type) {
	EventQueue* instance = EventQueue::getInstance();
	// if the type vector doesn't exist yet, create it.
	if (instance->eventHandlerVectorMap.count(type) == 0) {
		instance->eventHandlerVectorMap[type] = vector<EventHandler*>();
	}

	for (auto& eh : instance->eventHandlerVectorMap[type]) {
		if (eh == &handler) {
			// this handler is already registered as a listener, return
			return;
		}
	}
	
	instance->eventHandlerVectorMap[type].push_back(&handler);
	return;

}
void EventQueue::deregisterHandler(EventReceivingKey&& k, EventHandler& handler, EventType type) {
	EventQueue* instance = EventQueue::getInstance();
	int i = 0;
	for (auto& eh : instance->eventHandlerVectorMap[type]) {
		if (eh == &handler) {
			// below lines swap the current handler with the one at the back, then pop the back.
			// this operation is O(1), faster than reomving and re-sorting the vector.
			std::swap(instance->eventHandlerVectorMap[type][i], instance->eventHandlerVectorMap[type].back());
			instance->eventHandlerVectorMap[type].pop_back();
			// must return here, otherwise the iterator is invalid and will throw an error.
			return;
		}
		i++;
	}

}

void EventQueue::postEvent(EventPostingKey&& k, Event* e) {
	EventQueue* instance = EventQueue::getInstance();
	instance->events.push(EventPtr(e));
}

void EventQueue::processEvents() {
	while (this->events.empty() == false) {
		processEvent(this->events.front().get());
		this->events.pop();
	}
}

}