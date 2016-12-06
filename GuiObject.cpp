#include "GuiObject.hpp"

//DELETEME
#include <iostream>

std::string GuiObject::getId() {
	return this->m_id;
}

sf::Vector2f GuiObject::getPos() {
	return this->m_position;
}

int GuiObject::switchMouseInsideBool(bool pointInsideBounds) {
	
	if (!m_mouseInsideSwitch) {
		if (pointInsideBounds) {
			m_mouseInsideSwitch = true;
			return 1;
		}
	} else {
		if (!pointInsideBounds) {
			m_mouseInsideSwitch = false;
			return -1;
		}
	}

	return 0;

}

bool GuiObject::setHidden(bool hidden) {
	bool wasHiddenPreviously = m_isHidden;
	m_isHidden = hidden;
	return wasHiddenPreviously;
}

void GuiObject::setStyleAtlas(std::unordered_map<std::string, GuiStyle>* styleAtlas) {
	m_styleAtlas = styleAtlas;
}