#include "EventQueue.hpp"
/*
bool EventQueue::allocateNode(EventType eventType, EventHandler* handler) {

	int i = 0;
	while (i < this->maxNodes) {
		if (nodes[i]->object == nullptr) {
			nodes[i]->object = handler;
			if (listMap.count(eventType) == 0) {
				// if the listMap is empty for that eventType, initialise it 
				listMap[eventType] = nodes[i];
			}
			// found free node, use it!
			// now add it to the linked list at the start
			listMap[eventType]->previous = nodes[i];
			nodes[i]->next = listMap[eventType];
			listMap[eventType] = nodes[i];
			return true;
		}
		i++;
	}
	return false;
	// free node not found - shit's fucked son, something bad has happened

}

void EventQueue::deallocateNode(EventType eventType, EventHandler* handler) {
	
	//Loops thru listNode pool until it finds the matching object.
	//Once found, listnode is removed from the linked list

	int i = 0;
	while (i < this->maxNodes) {

		if (nodes[i]->object == handler) {
			nodes[i]->object = nullptr;
			if (nodes[i]->next == nullptr) {
				// it's at the end of the list
				nodes[i]->previous->next = nullptr;
			} else if (nodes[i]->previous = nullptr) {
				// it's at the beginning, need to set listMap
				nodes[i]->next->previous = nullptr;
				listMap[eventType] = nodes[i]->next;
			} else {
				// it's in the middle somewhere, do everything but listmap
				nodes[i]->previous->next = nodes[i]->next;
				nodes[i]->next->previous = nodes[i]->previous;
			}
			// clear this node's direction pointers
			nodes[i]->next = nullptr;
			nodes[i]->previous = nullptr;
			break;
		}

		i++;
	}
	//TODO heap big error here if it never finds the node?

}
*/

void EventQueue::processEvent(Event* e) {

	for (EventHandler* eh : this->vectorMap[e->type]) {
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
			this->vectorMap[type].erase(this->vectorMap[type].begin() + i);
		}
		i++;
	}

}

void EventQueue::postEvent(Event* e) {

	this->eventStream.push(e);

}

void EventQueue::processEvents() {

	while (this->eventStream.empty() == false) {
		processEvent(this->eventStream.front());
		this->eventStream.pop();
	}

}

EventQueue& EventQueue::getGlobal() {

	static EventQueue g(2048);

	return g;
	
}

EventQueue::EventQueue(unsigned int maxNodes) {

	

}

EventQueue::~EventQueue() {



}