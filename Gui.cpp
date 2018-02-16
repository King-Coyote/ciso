#include <iostream>
#include <string>

#include "Gui.hpp"
#include "EventHandler.hpp"


Gui::Gui(EventQueue& q, sf::RenderWindow& mainWindow, Resources& resourceMgr) : 
	EventHandler(q, {EventType::CREATE_GUI}),
	mainWindow(mainWindow), 
	resourceMgr(resourceMgr) 
{

	// DELETEME - DEfAULTIST TRAYSH
	this->m_styleMap["DEFAULT"] = std::shared_ptr<GuiStyle>(new GuiStyle(*this, resourceMgr, "DEFAULT"));

}

void Gui::update(const float dt) {

	bool mouseEnteredFired = false;

	// goes in reverse order so that objects that have just been added are "on top", meaning they
	// get update priority for e.g. mouse entering behaviour.
	for (auto it = guiObjs.rbegin(); it != guiObjs.rend(); ++it) {

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
	for (auto obj : guiObjs) {
		obj->draw(dt, this->mainWindow);
	}
	this->mainWindow.display();

}

void Gui::clear() {
	this->mainWindow.clear(sf::Color::Black);
}

void Gui::onCreateGui(std::shared_ptr<GuiObject> guiObj) {
	// loads the gui obj into the list
	if (this->m_styleMap.count(guiObj->getStyleId()) < 1) {
		// TODO: needs to return some kind of error, or throw an exception
		return;
	}
	guiObj->setStyle(this->m_styleMap[guiObj->getStyleId()]);
	this->guiObjs.push_back(guiObj);
}

void Gui::loadGuiObject(std::shared_ptr<GuiObject> obj) {
	if (this->m_styleMap.count(obj->getStyleId()) < 1) {
		// TODO: needs to return some kind of error, or throw an exception
		return;
	}
	obj->setStyle(this->m_styleMap[obj->getStyleId()]);
	this->guiObjs.push_back(obj);
}

bool Gui::mainWindowIsOpen() {
	return this->mainWindow.isOpen();
}