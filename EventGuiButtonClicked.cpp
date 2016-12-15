#include "Event.hpp"

EventGuiButtonClicked::EventGuiButtonClicked(std::string id, sf::Vector2i mousePos) :
	m_id(id),
	m_mousePos(mousePos)
{
	this->type = EventType::GUI_BUTTONCLICKED;
}

std::string EventGuiButtonClicked::getId() {
	return m_id;
}

sf::Vector2i EventGuiButtonClicked::getPos() {
	return m_mousePos;
}