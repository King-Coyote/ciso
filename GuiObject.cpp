#include "GuiObject.hpp"

std::string GuiObject::getId() {
	return this->m_id;
}

sf::Vector2f GuiObject::getPos() {
	return this->m_position;
}