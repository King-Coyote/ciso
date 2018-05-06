#include <iostream>

#include "Input.hpp"
#include "Event.hpp"
#include "EventQueue.hpp"

Input::Input(EventQueue& q, sf::RenderWindow& win) : 
	guiWindow(&win), 
	eventQ(&q) 
{}

void Input::update(const float dt) {
	sf::Event e;
	while (this->guiWindow->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			this->guiWindow->close();
		} else if (e.type != sf::Event::MouseMoved) {
			Event cie = Event(EventType::SFML_INPUT);
			cie.sfmlEvent = e;
			this->eventQ->postEvent(cie);
		}
	}
}