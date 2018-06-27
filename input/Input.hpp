#pragma once

#include <memory>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

namespace ci {

class EventQueue;

class Input {
public:
	Input(EventQueue& q, sf::RenderWindow& win);

	void update(const float dt);

private:
	sf::RenderWindow* guiWindow;
	EventQueue* eventQ;

};

}