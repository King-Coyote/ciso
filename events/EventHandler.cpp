#include "EventHandler.hpp"
#include "EventQueue.hpp"
#include "Event.hpp"

namespace ci {

EventHandler::EventHandler(EventQueue& eventQueue, std::vector<EventType> eventTypes) {
	for (auto type : eventTypes) {
		eventQueue.registerHandler(*this, type);
	}
}

void EventHandler::handleEvent(const Event& e) {
	switch(e.type) {
	case EventType::CREATE_GUI:
		this->onCreateGui(e.str);
		break;
	case EventType::SFML_INPUT:
		switch(e.sfmlEvent.type) {
		case sf::Event::EventType::MouseButtonPressed:
			this->onMousePress(e.sfmlEvent);
			break;
		case sf::Event::EventType::MouseButtonReleased:
			this->onMouseRelease(e.sfmlEvent);
			break;
		case sf::Event::EventType::MouseMoved:
			this->onMouseMove(e.sfmlEvent);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

}