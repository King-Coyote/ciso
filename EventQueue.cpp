#include "EventQueue.hpp"

bool EventQueue::allocateNode(EventType eventType, EventHandler* handler) {

	int i = 0;
	while (i < MAX_NODES) {
		if (nodes[i]->object == nullptr) {
			// found free node, use it!
			nodes[i]->object = handler;
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
	// TODO: send message or something here?

}

void EventQueue::deallocateNode(EventType eventType, EventHandler* handler) {
	
	/* Loops thru listNode pool until it finds the matching object.
	Once found, listnode is removed from the linked list*/

	int i = 0;
	while (i < MAX_NODES) {

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

EventQueue::EventQueue() {

	/*initialise ListNode pool and usedNodes*/
	for (int i = 0; i < MAX_NODES; i++) {
		nodes[i] = new ListNode<EventHandler>();
	}
	usedNodes = 0;

}

EventQueue::~EventQueue() {

	/*Free up all memory in the case that the event queue is deleted in the game without it quitting*/
	for (int i = 0; i < MAX_NODES; i++) {
		delete nodes[i];
	}

}