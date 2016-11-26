#include <iostream>
#include <string>

#include "Gui.hpp"

Gui::Gui(EventQueue& q, sf::RenderWindow& mainWindow) : mainQ(q), mainWindow(mainWindow) {

	this->mainQ.registerHandler(this, EventType::INPUT); // replace with more general input event type

}

void Gui::createGuiObject() {


}

void Gui::update(const float dt) {

	

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

	std::shared_ptr<EventSfmlInput> eventSF = std::static_pointer_cast<EventSfmlInput>(e);
	switch (eventSF->getSfmlType()) {
	case sf::Event::MouseEntered:

		break;
	}

}

bool Gui::mainWindowIsOpen() {
	return this->mainWindow.isOpen();
}