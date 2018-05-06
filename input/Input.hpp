#pragma once

#include <memory>

#include "Graphics.hpp"
#include "Window.hpp"

class EventQueue;

class Input {
public:
	Input(EventQueue& q, sf::RenderWindow& win);

	void update(const float dt);

private:
	sf::RenderWindow* guiWindow;
	EventQueue* eventQ;

};