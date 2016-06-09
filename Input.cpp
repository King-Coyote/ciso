#include "Input.hpp"

void Input::update(const float dt) {
	sf::Event e;
	while (this->guiWindow->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			this->guiWindow->close();
		}
	}
}