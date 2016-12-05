#include "GuiObject.hpp"

std::string GuiObject::getId() {
	return this->m_id;
}

sf::Vector2f GuiObject::getPos() {
	return this->m_position;
}

bool GuiObject::switchMouseInsideBool(bool pointInsideBounds) {
	
	if (!m_mouseInsideSwitch) {
		if (pointInsideBounds) {
			m_mouseInsideSwitch = true;
			return true;
		}
	} else {
		if (!pointInsideBounds) {
			m_mouseInsideSwitch = false;
		}
	}

	return false;

}

bool GuiObject::setHidden(bool hidden) {
	bool wasHiddenPreviously = m_isHidden;
	m_isHidden = hidden;
	return wasHiddenPreviously;
}