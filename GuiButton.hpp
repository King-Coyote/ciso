#pragma once

#include "GuiObject.hpp"

// if you need to add more states, ADD AFTER DISABLED AND BEFORE NUM_STATES
enum ButtonState {
	ENABLED = 0,
	CLICKED,
	HOVER,
	DISABLED,
	NUM_BUTTON_STATES
};

// Button class for the gui system. Obvis. Created using a CREATE_GUI event.
class GuiButton : public GuiObject {

private:

	sf::Text m_text;
	sf::RectangleShape m_sprite;

	ButtonState m_currentState;

	std::string m_stateStyleIds[NUM_BUTTON_STATES];

	ButtonState changeState(ButtonState destinationState);

public:

	GuiButton();
	GuiButton(std::string id, sf::Vector2f size, sf::Vector2f pos,
			std::string defaultGuiStyleName,
			std::string text = "");

	void setPos(sf::Vector2f pos);
	// setss the state to the new state and returns the old one.

	bool pointInsideBounds(sf::Vector2i point);

	void onMouseEntered();

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

};