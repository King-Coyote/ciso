#include "EventHandler.hpp"
#include "EventQueue.hpp"
#include "Event.hpp"

EventHandler::EventHandler(EventQueue& eventQueue, std::vector<EventType> eventTypes) {
	for (auto type : eventTypes) {
		eventQueue.registerHandler(*this, type);
	}
}