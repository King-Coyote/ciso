#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "SFML\Graphics.hpp"
#include "GuiStyle.hpp"

class GuiObject {

protected:
	std::string m_id;
	// position taken from top left of item
	sf::Vector2f m_position;

	static std::unordered_map<std::string, std::shared_ptr<GuiStyle>>* m_styleAtlas;

public:
	GuiObject() {}
	~GuiObject() {}

	std::string getId();
	sf::Vector2f getPos();

	virtual void draw(const float dt, sf::RenderWindow& win) {}
	virtual void update(const float dt) {}
};