#include <iostream>
#include <string>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Gui.hpp"

sf::RenderWindow* Gui::mainWinStatic = nullptr;

Gui::Gui(EventQueue* q) {

	this->mainQ = q;
	this->mainQ->registerHandler(this, EventType::INPUT); // replace with more general input event type
	this->mainWindow.create(sf::VideoMode(800, 600), "CoyoteIso");
	this->mainWindow.setFramerateLimit(60);
	Gui::mainWinStatic = &this->mainWindow;

}

void Gui::update(const float dt) {

	

}

void Gui::draw(const float dt) {

	this->mainWindow.display();

}

void Gui::clear() {
	this->mainWindow.clear(sf::Color::Black);
}

void Gui::handleEvent(Event* e) {

	EventSfmlInput* eventSF= static_cast<EventSfmlInput*>(e);
	switch (eventSF->getSfmlType()) {
	case sf::Event::MouseEntered:

		break;
	}

}

bool Gui::mainWindowIsOpen() {
	return this->mainWindow.isOpen();
}

sf::RenderWindow* Gui::getMainWin() {
	return mainWinStatic;
}