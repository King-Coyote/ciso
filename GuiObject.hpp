#pragma once

#include <string>
#include <vector>

#include "SFML\Graphics.hpp"

class GuiObject {

protected:
	std::string m_id;
	// position taken from top left of item
	sf::Vector2i m_position;

public:
	GuiObject() {}
	~GuiObject() {}

	std::string getId();
	sf::Vector2i getPos();

	virtual void draw(const float dt, sf::RenderWindow& win) {}
	virtual void update(const float dt) {}
};