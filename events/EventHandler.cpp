#include "EventHandler.hpp"
#include "EventQueue.hpp"
#include "Event.hpp"

namespace ci {

EventHandler::EventHandler(std::vector<EventType> eventTypes) :
	types(eventTypes)
{
	for (auto type : eventTypes) {
		EventQueue::registerHandler({}, *this, type);
	}
}

EventHandler::~EventHandler() {
	for (auto type : this->types) {
		EventQueue::deregisterHandler({}, *this, type);
	}
}

void EventHandler::handleEvent(Event* e) {
	switch(e->getType()) {
	case EventType::CREATE_GUI: {
		EventCreateGui* cgep = static_cast<EventCreateGui*>(e);
		this->onCreateGui(cgep);
		break;
	}
	case EventType::SFML_INPUT: {
		EventInput* ie = static_cast<EventInput*>(e);
		switch(ie->sfEvent.type) {
		case sf::Event::EventType::MouseButtonPressed:
			this->onMousePress(ie);
			break;
		case sf::Event::EventType::MouseButtonReleased:
			this->onMouseRelease(ie);
			break;
		case sf::Event::EventType::MouseMoved:
			this->onMouseMove(ie);
			break;
		case sf::Event::EventType::TextEntered:
			this->onTextEntered(ie);
			break;
		case sf::Event::EventType::KeyPressed:
			this->onKeyPressed(ie);
			break;
		case sf::Event::EventType::KeyReleased:
			this->onKeyReleased(ie);
			break;
		default:
			break;
		}
		break;
	}
	case EventType::GUI_BUTTONCLICKED: {
		EventGuiButtonClicked* egbc = static_cast<EventGuiButtonClicked*>(e);
		this->onGuiButtonClicked(egbc);
		break;
	}
	case EventType::RUNSCRIPT: {
		EventRunScript* ers = static_cast<EventRunScript*>(e);
		this->onRunScript(ers);
	}
	case EventType::GAME_COMMAND_MOVE: {
		EventGameCommandMove* egcm = static_cast<EventGameCommandMove*>(e);
		this->onCommandMove(egcm);
	}
	default:
		break;
	}
}

}