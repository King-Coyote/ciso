#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>

#include "Event.hpp"
#include "EventHandler.hpp"

using namespace std;

namespace ci {

class EventQueue {
public: // METHODS
	EventQueue() {};
	~EventQueue() {}

	void registerHandler(EventHandler& handler, EventType type);
	void deregisterHandler(EventHandler& handler, EventType type);

	void postEvent(const Event& e);
	void processEvents();
private: // MEMBERS
	unordered_map<EventType, vector<EventHandler*>> eventHandlerVectorMap;
	queue<Event> events;
	void processEvent(const Event& e);

};

}