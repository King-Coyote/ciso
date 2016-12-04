#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "SFML\Graphics.hpp"

class GuiObject {

protected:
	std::string m_id;
	// position taken from top left of item
	sf::Vector2f m_position;

public:
	GuiObject() {}
	~GuiObject() {}

	std::string getId();
	sf::Vector2f getPos();

	virtual bool pointInsideBounds(sf::Vector2i point) { return false; }

	// Gui-object specific events (NOTE: very much distinct from main events system. Only for use on guiObjects.)
	virtual void onMouseEntered() {}
	virtual void onMouseExited() {}
	virtual void onClick() {}
	virtual void onUnClick() {}

	virtual void draw(const float dt, sf::RenderWindow& win) {}
	virtual void update(const float dt) {}
};