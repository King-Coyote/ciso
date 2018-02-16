#pragma once

#include <memory>

#include "Graphics.hpp"
#include "EventQueue.hpp"

class Input {

private:

	sf::RenderWindow& guiWindow;
	EventQueue& eventQ;

public:

	Input(EventQueue& q, sf::RenderWindow& win) : guiWindow(win), eventQ(q) {}

	void update(const float dt);

};