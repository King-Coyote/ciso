#include <iostream>

#include "Input.hpp"
#include "Event.hpp"
#include "EventQueue.hpp"

namespace ci {

Input::Input(sf::RenderWindow& win) : 
	guiWindow(&win)
{}

void Input::update(const float dt) {
	sf::Event e;
	while (this->guiWindow->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			this->guiWindow->close();
		} else {
			this->postEvent(new EventInput(e));
		}
	}
}

}