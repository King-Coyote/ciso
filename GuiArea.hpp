#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "GuiObject.hpp"

class GuiArea : public GuiObject {

private:

	std::vector<std::shared_ptr<GuiObject>> m_guiObjects;

public:

	GuiArea();
	GuiArea(std::vector<std::shared_ptr<GuiObject>>);

	void setPos(sf::Vector2f pos);

	bool pointInsideBounds(sf::Vector2i point);

	void onMouseEntered();
	void onMouseExited();
	void onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);
	void onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

};
