#include "Event.hpp"

EventGuiButtonClicked::EventGuiButtonClicked(std::string id, sf::Vector2i mousePos) :
	buttonId(id),
	mousePos(mousePos)
{
	this->type = EventType::GUI_BUTTONCLICKED;
}

std::string EventGuiButtonClicked::getButtonId() {
	return this->buttonId;
}

sf::Vector2i EventGuiButtonClicked::getMousePos() {
	return this->mousePos;
}