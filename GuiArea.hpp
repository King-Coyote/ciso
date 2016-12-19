#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "GuiObject.hpp"

enum GuiAreaState {
	ENABLED = 0,
	CLICKED,
	HOVER,
	DISABLED,
	NUM_BUTTON_STATES
};

class GuiArea : public GuiObject {

private:

	std::vector<std::shared_ptr<GuiObject>> m_guiObjs;

public:

	GuiArea();
	GuiArea(std::vector<std::shared_ptr<GuiObject>>);

	void setPos(sf::Vector2f newPos);

	bool pointInsideBounds(sf::Vector2i point);

	SwitchResult switchMouseInsideBool(sf::Vector2i mousePos);

	void onMouseEntered();
	void onMouseExited();
	void onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);
	void onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

};
