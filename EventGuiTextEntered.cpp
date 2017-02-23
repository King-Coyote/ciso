#include "Event.hpp"

EventGuiTextEntered::EventGuiTextEntered(std::string id, sf::String textEntered) :
	m_id(id),
	textEntered(textEntered),
	Event(EventType::GUI_TEXTENTERED)
{}

sf::String EventGuiTextEntered::getTextEntered() {
	return this->textEntered;
}

std::string EventGuiTextEntered::getId() {
	return this->m_id;
}