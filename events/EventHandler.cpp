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
			switch(e.sfmlEvent.mouseButton.button) {
			case sf::Mouse::Button::Left:
				this->onLeftClick(sf::Vector2f(e.sfmlEvent.mouseButton.x, e.sfmlEvent.mouseButton.y));
				break;
			case sf::Mouse::Button::Right:
				this->onRightClick(sf::Vector2f(e.sfmlEvent.mouseButton.x, e.sfmlEvent.mouseButton.y));
				break;
			default:
				break;
			}
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