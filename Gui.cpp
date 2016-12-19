#include <iostream>
#include <string>

#include "Gui.hpp"


Gui::Gui(EventQueue& q, sf::RenderWindow& mainWindow) : mainQ(q), mainWindow(mainWindow) {

	this->mainQ.registerHandler(this, EventType::INPUT); // replace with more general input event type
	this->mainQ.registerHandler(this, EventType::CREATE_GUI);

}

void Gui::update(const float dt) {

	bool mouseEnteredFired = false;

	// goes in reverse order so that objects that have just been added are "on top", meaning they
	// get update priority for e.g. mouse entering behaviour.
	for (auto it = m_guiObjs.rbegin(); it != m_guiObjs.rend(); ++it) {

		// this is done prior to update calls so that the GUI system can restrict it to only one
		// gui objet per frame.
		SwitchResult enterSwitch = it->get()->switchMouseInsideBool(sf::Mouse::getPosition(this->mainWindow));

		if (!mouseEnteredFired && 
			(enterSwitch == SwitchResult::ENTERED || enterSwitch == SwitchResult::ENTERED_CHILD)) {

			mouseEnteredFired = true;
			if (enterSwitch == SwitchResult::ENTERED) {
				it->get()->onMouseEntered();
			}
		}

		if (enterSwitch == SwitchResult::EXITED) {
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
		this->m_guiObjs.push_back(eventCG->getGuiObj());
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
		}
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