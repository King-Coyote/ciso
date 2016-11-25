#include <iostream>
#include <string>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Gui.hpp"

Gui::Gui(EventQueue& q, sf::RenderWindow& mainWindow) : mainQ(q), mainWindow(mainWindow) {

	this->mainQ.registerHandler(this, EventType::INPUT); // replace with more general input event type

}

void Gui::update(const float dt) {

	

}

void Gui::draw(const float dt) {

	//for (auto& obj : this->m_guiObjects) {
	//	obj.draw(dt);
	//}
	//this->mainWindow.display();

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