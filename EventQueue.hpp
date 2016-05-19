#pragma once

#include <unordered_map>
#include <vector>
#include <queue>

#include "Event.hpp"
#include "EventHandler.hpp"
#include "ListNode.hpp"

class EventQueue {

private:

	static EventQueue& global;

	std::unordered_map<EventType, std::vector<EventHandler*>> vectorMap;

	/*
	//TODO: delete unused variables lol
	unsigned int maxNodes;
	unsigned int usedNodes;
	ListNode<EventHandler>* nodes[];
	
	bool allocateNode(EventType eventType, EventHandler* handler);
	void deallocateNode(EventType eventType, EventHandler* handler);
	*/

	std::queue<Event*> eventStream;

	void processEvent(Event* e);

public:

	static EventQueue& getGlobal();

	EventQueue(unsigned int MAX_NODES);
	~EventQueue();

	void registerHandler(EventHandler* handler, EventType type);
	void deregisterHandler(EventHandler* handler, EventType type);

	void postEvent(Event* e);
	void processEvents();

};