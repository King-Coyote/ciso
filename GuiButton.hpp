#pragma once

#include "GuiObject.hpp"
#include "EventQueue.hpp"

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
	ButtonState m_defaultState;
	std::string m_stateStyleIds[NUM_BUTTON_STATES];

	// main event queue, if any
	EventQueue* m_mainQ;

	// setss the state to the new state and returns the old one.
	ButtonState changeState(ButtonState destinationState);

public:

	GuiButton();
	GuiButton(
		std::string id, sf::Vector2f size, sf::Vector2f pos,
		std::string defaultGuiStyleName,
		std::string text = "",
		EventQueue* mainQ = nullptr
	);

	void setPos(sf::Vector2f pos);
	void setStateStyleId(ButtonState state, std::string newId);

	bool pointInsideBounds(sf::Vector2i point);

	void onMouseEntered();
	void onMouseExited();
	void onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);
	void onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

};