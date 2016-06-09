#pragma once

#include "SFML\Graphics.hpp"
#include "EventQueue.hpp"

class Input {

private:

	sf::RenderWindow* guiWindow;
	EventQueue* eventQ;

public:

	Input(EventQueue* q, sf::RenderWindow* win);

	void update(const float dt);

};