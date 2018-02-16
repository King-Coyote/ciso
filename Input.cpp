#include <iostream>

#include "Input.hpp"
#include "Event.hpp"
#include "EventQueue.hpp"

void Input::update(const float dt) {
	sf::Event e;
	while (this->guiWindow.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			this->guiWindow.close();
		} else if (e.type != sf::Event::MouseMoved) {
			this->eventQ.postEvent(std::shared_ptr<EventSfmlInput>(new EventSfmlInput(e)));
		}
	}
}