#pragma once

#include "SFML\Graphics.hpp"
#include "EventQueue.hpp"

class Input {

private:

	sf::RenderWindow* guiWindow;
	EventQueue* eventQ;

public:

	Input(EventQueue* q, sf::RenderWindow* win) : eventQ(q), guiWindow(win) {};

	void update(const float dt);

};