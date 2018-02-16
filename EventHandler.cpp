#include "EventHandler.hpp"
#include "EventQueue.hpp"
#include "Event.hpp"

EventHandler::EventHandler(EventQueue& eventQueue, std::vector<EventType> eventTypes) {
	for (auto type : eventTypes) {
		eventQueue.registerHandler(this, type);
	}
}

/*
VOID,
DEBUG,
INPUT,
CREATE_GUI, CREATE_GUI_LIST,
GUI_BUTTONCLICKED, GUI_TEXTENTERED
*/
void EventHandler::handleEvent(std::shared_ptr<Event> e) {
	
	switch (e->type) {
	case EventType::DEBUG: {
		std::shared_ptr<EventDebug> ed = std::static_pointer_cast<EventDebug>(e);
		onDebug(ed->getMsg(), ed->getLevel());
		break;
	}
	case EventType::GUI_BUTTONCLICKED: {
		std::shared_ptr<EventGuiButtonClicked> egbc = std::static_pointer_cast<EventGuiButtonClicked>(e);
		onGuiButtonClicked(egbc->getButtonId(), egbc->getMousePos());
		break;
	}
	case EventType::GUI_TEXTENTERED: {
		std::shared_ptr<EventGuiTextEntered> egte = std::static_pointer_cast<EventGuiTextEntered>(e);
		onGuiTextFieldEntered(egte->getId(), egte->getTextEntered());
		break;
	}
	case EventType::CREATE_GUI: {
		std::shared_ptr<EventCreateGui> ecg = std::static_pointer_cast<EventCreateGui>(e);
		onCreateGui(ecg->getGuiObj());
		break;
	}
	case EventType::CREATE_GUI_LIST: {
		std::shared_ptr<EventCreateGuiList> ecgl = std::static_pointer_cast<EventCreateGuiList>(e);
		onCreateGuiList(ecgl->getGuiObjList());
		break;
	}
	case EventType::INPUT: {
		std::shared_ptr<EventSfmlInput> eventSF = std::static_pointer_cast<EventSfmlInput>(e);
		switch (eventSF->getEventPtr()->type) {
		case sf::Event::KeyPressed: {
			onKeyPressed(eventSF->getEventPtr()->key.code);
			break;
		}
		case sf::Event::MouseButtonPressed: {
			onMouseButtonPressed(
				sf::Vector2i(eventSF->getEventPtr()->mouseButton.x, eventSF->getEventPtr()->mouseButton.y),
				eventSF->getEventPtr()->mouseButton.button
			);
			break;
		}
		case sf::Event::MouseButtonReleased: {
			onMouseButtonReleased(
				sf::Vector2i(eventSF->getEventPtr()->mouseButton.x, eventSF->getEventPtr()->mouseButton.y),
				eventSF->getEventPtr()->mouseButton.button
			);
			break;
		}
		case sf::Event::TextEntered: {
			onTextEntered(eventSF->getEventPtr()->text.unicode);
			break;
		}
		}
	}
	default: {

	}
	}

}