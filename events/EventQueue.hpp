#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>

#include "Event.hpp"
#include "EventHandler.hpp"

namespace ci {

typedef std::unique_ptr<Event> EventPtr;

class EventQueue {
public: // METHODS
	EventQueue() {};
	~EventQueue() {}

	void registerHandler(EventHandler& handler, EventType type);
	void deregisterHandler(EventHandler& handler, EventType type);

	void postEvent(Event* e);
	void processEvents();
private: // MEMBERS
	unordered_map<EventType, std::vector<EventHandler*>> eventHandlerVectorMap;
	std::queue<EventPtr> events;
	void processEvent(Event* e);

};

}