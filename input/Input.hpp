#pragma once

#include <memory>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "EventSender.hpp"

namespace ci {

class EventQueue;

class Input : public EventSender {
public:
	Input(sf::RenderWindow& win);

	void update(const float dt);

private:
	sf::RenderWindow* guiWindow;
};

}