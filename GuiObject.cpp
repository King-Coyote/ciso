#include "GuiObject.hpp"

//DELETEME
#include <iostream>

std::string GuiObject::getId() {
	return this->m_id;
}

sf::Vector2f GuiObject::getPos() {
	return this->m_position;
}

void GuiObject::setPos(sf::Vector2f newPos) {
	m_position = newPos;
}

SwitchResult GuiObject::switchMouseInsideBool(sf::Vector2i mousePos) {

	bool pointInsideBounds = this->pointInsideBounds(mousePos);
	
	if (!m_mouseInsideSwitch) {
		if (pointInsideBounds) {
			m_mouseInsideSwitch = true;
			return SwitchResult::ENTERED;
		}
	} else {
		if (!pointInsideBounds) {
			m_mouseInsideSwitch = false;
			return SwitchResult::EXITED;
		}
	}

	return SwitchResult::NOTHING;

}

bool GuiObject::setHidden(bool hidden) {
	bool wasHiddenPreviously = m_isHidden;
	m_isHidden = hidden;
	return wasHiddenPreviously;
}

void GuiObject::setStyleAtlas(std::unordered_map<std::string, GuiStyle>* styleAtlas) {
	m_styleAtlas = styleAtlas;
}