#include "GuiObject.hpp"

std::string GuiObject::getId() {
	return this->m_id;
}

sf::Vector2f GuiObject::getPos() {
	return this->m_position;
}

void GuiObject::setPos(sf::Vector2f newPos) {
	m_position = newPos;
}

sf::Vector2f GuiObject::getSize() {
	return m_size;
}

void GuiObject::setSize(sf::Vector2f newSize) {
	m_size = newSize;
}

SwitchResult GuiObject::switchMouseInsideBool(sf::Vector2i mousePos, bool occluded) {

	bool inBoundsAndNotOccluded = (this->pointInsideBounds(mousePos) && !occluded);

	if (!m_mouseInsideSwitch) {
		if (inBoundsAndNotOccluded) {
			m_mouseInsideSwitch = true;
			return SwitchResult::GUISWITCH_ENTERED;
		} else {
			return SwitchResult::GUISWITCH_OUTSIDE;
		}
	} else {
		if (!inBoundsAndNotOccluded) {
			m_mouseInsideSwitch = false;
			return SwitchResult::GUISWITCH_EXITED;
		} else {
			return SwitchResult::GUISWITCH_INSIDE;
		}
	}

}

bool GuiObject::setHidden(bool hidden) {
	bool wasHiddenPreviously = m_isHidden;
	m_isHidden = hidden;
	return wasHiddenPreviously;
}

void GuiObject::setStyle(std::shared_ptr<GuiStyle> style) {
	this->m_guiStyle = style;
}

std::string GuiObject::getStyleId() {
	return this->styleId;
}