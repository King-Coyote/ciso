#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>

#include "Event.hpp"
#include "EventHandler.hpp"

namespace ci {

typedef std::unique_ptr<Event> EventPtr;

class EventPostingKey;
class EventReceivingKey;

class EventQueue {
public: // METHODS

	// boi u better make sure this eventqueue is thread safe
	static EventQueue* 	getInstance();
	void 				processEvents();

	// KEY PROTECTED METHODS
	static void registerHandler(EventReceivingKey&& k, EventHandler& handler, EventType type);
	static void deregisterHandler(EventReceivingKey&& k, EventHandler& handler, EventType type);

	static void postEvent(EventPostingKey&& k, Event* e);

private:
	// MEMBERS
	unordered_map<EventType, std::vector<EventHandler*>> eventHandlerVectorMap;
	std::queue<EventPtr> events;
	void processEvent(Event* e);
	static std::unique_ptr<EventQueue> instance;

	//METHODS
	// NOW LISTEN HERE.
	// YES, singletons suck
	// AND: am I a dickhead for using one? Also yes.
	// BUT, uh, know this, friend:
	// the only thing that will be allowed to access this is the eventHandler, or whatever is declared a friend of EventReceivingKey
	// so that anything that inherits eventhandler will jsut know how to receive events.
	// any class wishing to POST events will have to explicitly receive this class from its creator.
	// (which will have to be a friend of EventPostingKey)
	EventQueue() {}
	EventQueue(EventQueue&) = delete;

};

class EventReceivingKey {
private:
	friend class EventHandler;
	EventReceivingKey(EventReceivingKey&) = delete;
	EventReceivingKey() {}
};

class EventPostingKey {
private:
	friend class EventSender;
	EventPostingKey(EventPostingKey&) = delete;
	EventPostingKey() {}
};

}