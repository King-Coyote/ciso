#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>

#include "Event.hpp"
#include "EventHandler.hpp"

class EventQueue {

private:

	// map of the event handler vectors, by event type
	std::unordered_map<EventType, std::vector<EventHandler*>> eventHandlerVectorMap;

	std::queue<std::shared_ptr<Event>> eventStream;

	void processEvent(std::shared_ptr<Event> e);

public:

	//static EventQueue& getGlobal();

	EventQueue() {};
	~EventQueue();

	void registerHandler(EventHandler* handler, EventType type);
	void deregisterHandler(EventHandler* handler, EventType type);

	void postEvent(std::shared_ptr<Event> e);
	void processEvents();

};