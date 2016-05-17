#pragma once

#include <unordered_map>

#include "Event.hpp"
#include "EventHandler.hpp"
#include "ListNode.hpp"

class EventQueue {

private:

	std::unordered_map<EventType, ListNode<EventHandler>*> listMap;

	//TODO: delete unused variables lol
	static const unsigned int MAX_NODES = 2048;
	unsigned int usedNodes;
	ListNode<EventHandler>* nodes[MAX_NODES];

	bool allocateNode(EventType eventType, EventHandler* handler);
	void deallocateNode(EventType eventType, EventHandler* handler);

public:

	EventQueue();
	~EventQueue();

};