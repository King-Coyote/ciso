#include <iostream>
#include <string>

#include "Gui.hpp"


Gui::Gui(EventQueue& q, sf::RenderWindow& mainWindow) : mainQ(q), mainWindow(mainWindow) {

	this->mainQ.registerHandler(this, EventType::INPUT); // replace with more general input event type
	this->mainQ.registerHandler(this, EventType::CREATE_GUI);

}

void Gui::update(const float dt) {

	bool mouseEnteredFired = false;

	for (auto obj : m_guiObjs) {

		// this is done prior to update calls so that the GUI system can restrict it to only one
		// gui objet per frame.

		int enterSwitch = obj->switchMouseInsideBool(obj->pointInsideBounds(sf::Mouse::getPosition(this->mainWindow)));
		
		if (!mouseEnteredFired && enterSwitch == 1) {
			obj->onMouseEntered();
			mouseEnteredFired = true;
		}

		if (enterSwitch == -1) {
			obj->onMouseExited();
		}

		obj->update(dt);
	}

}

void Gui::draw(const float dt) {

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
		this->m_guiObjs.push_back(eventCG->getGuiObj());
		break;
	}
	default:
		std::shared_ptr<EventSfmlInput> eventSF = std::static_pointer_cast<EventSfmlInput>(e);
		switch (eventSF->getSfmlType()) {
		case sf::Event::MouseButtonPressed:
			for (auto obj : m_guiObjs) {
				obj->onClick();
			}
			break;
		}
	}

}

std::shared_ptr<sf::Font> Gui::getFontPtr(std::string fontName) {
	if (m_fontMap.count(fontName) > 0) {
		return m_fontMap.at(fontName);
	} else {
		return m_fontMap.at("DEFAULT_FONT");
	}
}

std::shared_ptr<sf::Texture> Gui::getTexturePtr(std::string textureName) {
	if (m_textureMap.count(textureName) > 0) {
		return m_textureMap.at(textureName);
	} else {
		return m_textureMap.at("DEFAULT_TEXTURE");
	}
}

bool Gui::mainWindowIsOpen() {
	return this->mainWindow.isOpen();
}