#include "GuiArea.hpp"

GuiArea::GuiArea() {

}

GuiArea::GuiArea(std::vector<std::shared_ptr<GuiObject>>) {

}

void GuiArea::setPos(sf::Vector2f pos) {

	for (auto obj : m_guiObjs) {
		obj->setPos(sf::Vector2f(m_position.x + obj->getPos().x, m_position.y + obj->getPos().y));
	}

}

bool GuiArea::pointInsideBounds(sf::Vector2i point) {
	return false;
}

// override of GuiObject one. This needs to look inside at all the objects and essentially do what 
// the gui system does.
SwitchResult GuiArea::switchMouseInsideBool(sf::Vector2i mousePos) {

	bool mouseEnteredFired = false;

	SwitchResult returnVal = SwitchResult::NOTHING;

	// goes in reverse order so that objects that have just been added are "on top", meaning they
	// get update priority for e.g. mouse entering behaviour.
	for (auto it = m_guiObjs.rbegin(); it != m_guiObjs.rend(); ++it) {

		// this is done prior to update calls so that the GUI system can restrict it to only one
		// gui objet per frame.
		SwitchResult enterSwitch = it->get()->switchMouseInsideBool(mousePos);

		if (!mouseEnteredFired && 
			(enterSwitch == SwitchResult::ENTERED || enterSwitch == SwitchResult::ENTERED_CHILD)) {

			mouseEnteredFired = true;
			if (enterSwitch == SwitchResult::ENTERED) {
				it->get()->onMouseEntered();
			}
			returnVal = SwitchResult::ENTERED_CHILD;
		}

		if (enterSwitch == SwitchResult::EXITED) {
			it->get()->onMouseExited();
		}

	}

	if (!mouseEnteredFired) {
		// do the normal FSM behaviour for guiobjs.

		bool pointInsideBounds = this->pointInsideBounds(mousePos);

		if (!m_mouseInsideSwitch) {
			if (pointInsideBounds) {
				m_mouseInsideSwitch = true;
				returnVal = SwitchResult::ENTERED;
			}
		} else {
			if (!pointInsideBounds) {
				m_mouseInsideSwitch = false;
				returnVal = SwitchResult::EXITED;
			}
		}

	}

	return returnVal;

}

void GuiArea::onMouseEntered() {

}

void GuiArea::onMouseExited() {

}

void GuiArea::onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

}

void GuiArea::onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

}

void GuiArea::draw(const float dt, sf::RenderWindow& win) {

}

void GuiArea::update(const float dt) {

	for (auto obj : m_guiObjs) {
		obj->update(dt);
	}

}