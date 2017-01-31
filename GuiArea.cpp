#include "GuiArea.hpp"

GuiArea::GuiArea(std::string id, sf::Vector2f position, sf::Vector2f size) {
	m_id = id;
	m_size = size;
	this->setPos(position);
}

GuiArea::GuiArea(
	std::string id, sf::Vector2f position, sf::Vector2f size, std::vector<std::shared_ptr<GuiObject>> ptrVector
) { 
	m_id = id;
	m_guiObjs = ptrVector;
	m_size = size;
	this->setPos(position);
}

GuiArea::GuiArea(
	std::string id, sf::Vector2f position, sf::Vector2f size, std::vector<GuiObject*> vector
) {
	m_id = id;
	for (auto obj : vector) {
		std::shared_ptr<GuiObject> ptr(obj);
		m_guiObjs.push_back(ptr);
	}
	m_size = size;
	this->setPos(position);
}

void GuiArea::setPos(sf::Vector2f pos) {

	m_position = pos;

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

	SwitchResult returnVal = GUISWITCH_NOTHING;

	// goes in reverse order so that objects that have just been added are "on top", meaning they
	// get update priority for e.g. mouse entering behaviour.
	for (auto it = m_guiObjs.rbegin(); it != m_guiObjs.rend(); ++it) {
		// this is done prior to update calls so that the GUI system can restrict it to only one
		// gui objet per frame.
		SwitchResult enterSwitch = it->get()->switchMouseInsideBool(mousePos);
		if (!mouseEnteredFired && 
			(enterSwitch == GUISWITCH_ENTERED || enterSwitch == GUISWITCH_ENTERED_CHILD)) {

			mouseEnteredFired = true;
			if (enterSwitch == GUISWITCH_ENTERED) {
				it->get()->onMouseEntered();
			}
			returnVal = GUISWITCH_ENTERED_CHILD;
		}

		if (enterSwitch == GUISWITCH_EXITED) {
			it->get()->onMouseExited();
		}

	}

	if (!mouseEnteredFired) {
		// do the normal FSM behaviour for guiobjs.
		bool pointInsideBounds = this->pointInsideBounds(mousePos);
		if (!m_mouseInsideSwitch) {
			if (pointInsideBounds) {
				m_mouseInsideSwitch = true;
				returnVal = GUISWITCH_ENTERED;
			}
		} else {
			if (!pointInsideBounds) {
				m_mouseInsideSwitch = false;
				returnVal = GUISWITCH_EXITED;
			}
		}

	}

	return returnVal;

}

void GuiArea::addObj(GuiObject* obj) {
	std::shared_ptr<GuiObject> ptr(obj);
	m_guiObjs.push_back(ptr);
	ptr->setPos(sf::Vector2f(m_position.x + obj->getPos().x, m_position.y + obj->getPos().y));
}

void GuiArea::addObj(std::shared_ptr<GuiObject> obj) {
	m_guiObjs.push_back(obj);
}

void GuiArea::onMouseEntered() {

}

void GuiArea::onMouseExited() {

}

void GuiArea::onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	for (auto obj : m_guiObjs) {
		obj->onClick(mousePos, mouseButton);
	}

}

void GuiArea::onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	for (auto obj : m_guiObjs) {
		obj->onUnClick(mousePos, mouseButton);
	}

}

void GuiArea::draw(const float dt, sf::RenderWindow& win) {

	for (auto obj : m_guiObjs) {
		obj->draw(dt, win);
	}

}

void GuiArea::update(const float dt) {

	for (auto obj : m_guiObjs) {
		obj->update(dt);
	}

}