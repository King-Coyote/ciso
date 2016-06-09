#include <iostream>

#include "Input.hpp"
#include "Event.hpp"

Input::Input(EventQueue* q, sf::RenderWindow* win) {
	this->eventQ = q;
	this->guiWindow = win;
}

void Input::update(const float dt) {
	sf::Event e;
	while (this->guiWindow->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			this->guiWindow->close();
		} else {
			this->eventQ->postEvent(EventSfmlInput(e));
		}
	}
}