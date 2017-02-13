#include <iostream>
#include <string>

#include "Gui.hpp"


Gui::Gui(EventQueue& q, sf::RenderWindow& mainWindow, Resources& resourceMgr) : 
	mainQ(q), mainWindow(mainWindow), m_resourceMgr(resourceMgr) {

	this->mainQ.registerHandler(this, EventType::INPUT); // replace with more general input event type
	this->mainQ.registerHandler(this, EventType::CREATE_GUI);

	// DELETEME - DEfAULTIST TRAYSH
	this->m_styleMap["DEFAULT"] = std::shared_ptr<GuiStyle>(new GuiStyle(*this, resourceMgr, "DEFAULT"));

}

void Gui::update(const float dt) {

	bool mouseEnteredFired = false;

	// goes in reverse order so that objects that have just been added are "on top", meaning they
	// get update priority for e.g. mouse entering behaviour.
	for (auto it = m_guiObjs.rbegin(); it != m_guiObjs.rend(); ++it) {

		// this is done prior to update calls so that the GUI system can restrict it to only one
		// gui objet per frame.
		SwitchResult enterSwitch = it->get()->switchMouseInsideBool(sf::Mouse::getPosition(this->mainWindow), mouseEnteredFired);

		if (!mouseEnteredFired && 
			(enterSwitch == GUISWITCH_ENTERED || enterSwitch == GUISWITCH_ENTERED_CHILD || enterSwitch == GUISWITCH_INSIDE)) {

			mouseEnteredFired = true;
			if (enterSwitch == GUISWITCH_ENTERED) {
				it->get()->onMouseEntered();
			}
		}

		if (enterSwitch == GUISWITCH_EXITED) {
			it->get()->onMouseExited();
		}

		it->get()->update(dt);
	}

}

void Gui::draw(const float dt) {

	// NOT done in reverse, because things that have just been added should be drawn LAST i.e. ON TOP.
	for (auto obj : m_guiObjs) {
		obj->draw(dt, this->mainWindow);
	}
	this->mainWindow.display();

}

void Gui::clear() {
	this->mainWindow.clear(sf::Color::Black);
}

void Gui::handleEvent(std::shared_ptr<Event> e) {

	switch (e->type) {
	case EventType::CREATE_GUI: {
		std::shared_ptr<EventCreateGui> eventCG = std::static_pointer_cast<EventCreateGui>(e);
		loadGuiObject(eventCG->getGuiObj());
		break;
	}
	case EventType::INPUT: {
		std::shared_ptr<EventSfmlInput> eventSF = std::static_pointer_cast<EventSfmlInput>(e);
		switch (eventSF->getEventPtr()->type) {
		case sf::Event::MouseButtonPressed: {
			sf::Vector2i pos = sf::Vector2i(
				eventSF->getEventPtr()->mouseButton.x,
				eventSF->getEventPtr()->mouseButton.y
			);
			for (auto obj : m_guiObjs) {
				obj->onClick(pos, eventSF->getEventPtr()->mouseButton.button);
			}
			break;
		}
		case sf::Event::MouseButtonReleased: {
			sf::Vector2i pos = sf::Vector2i(
				eventSF->getEventPtr()->mouseButton.x,
				eventSF->getEventPtr()->mouseButton.y
			);
			for (auto obj : m_guiObjs) {
				obj->onUnClick(pos, eventSF->getEventPtr()->mouseButton.button);
			}
			break;
		}
		case sf::Event::KeyPressed: {
			for (auto obj : m_guiObjs) {
				obj->onKeyPressed(eventSF->getEventPtr()->key);
			}
		}
		}
	}
	}

}

void Gui::loadGuiObject(std::shared_ptr<GuiObject> obj) {
	if (this->m_styleMap.count(obj->getStyleId()) < 1) {
		// TODO: needs to return some kind of error, or throw an exception
		return;
	}
	obj->setStyle(this->m_styleMap[obj->getStyleId()]);
	this->m_guiObjs.push_back(obj);
}

bool Gui::mainWindowIsOpen() {
	return this->mainWindow.isOpen();
}