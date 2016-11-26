#pragma once

#include "SFML\Graphics.hpp"

class GameObject {

public:

	virtual void update(const float dt) {};
	virtual void draw(const float dt, sf::RenderWindow& win) {};

};
