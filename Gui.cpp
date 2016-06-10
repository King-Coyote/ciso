#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Gui.hpp"

Gui::Gui(EventQueue* q) {

	this->mainQ = q;
	this->mainQ->registerHandler(this, EventType::INPUT); // replace with more general input event type
	this->mainWindow.create(sf::VideoMode(800, 600), "My window");
	this->mainWindow.setFramerateLimit(60);

}

void Gui::update(const float dt) {

	

}

void Gui::draw(const float dt) {



}

void Gui::handleEvent(const Event& e) {

	if (e.type == EventType::INPUT) {
		Event eCopy = e;
		EventSfmlInput* eSfml = static_cast<EventSfmlInput*>(&eCopy);
		switch (eSfml->getSfmlType()) {
		case sf::Event::MouseEntered:
			std::cout << "MOUSE ENTERED\n";
			break;
		case sf::Event::MouseButtonPressed:
			std::cout << "MOUSE PRESSED\n";
			break;
		default:
			std::cout << "DIFFERENT EVENT\n";
			break;
		}
	}

}

bool Gui::mainWindowIsOpen() {
	return this->mainWindow.isOpen();
}

sf::RenderWindow* Gui::getMainWin() {
	return &this->mainWindow;
}