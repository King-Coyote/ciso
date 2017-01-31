#pragma once

#include "GuiObject.hpp"
#include "EventQueue.hpp"

// Button class for the gui system. Obvis. Created using a CREATE_GUI event.
class GuiButton : public GuiObject {

private:

	sf::Text m_text;
	sf::ConvexShape sprite;

	GuiState m_currentState;
	GuiState m_defaultState;

	// main event queue, if any
	EventQueue* m_mainQ;

	// setss the state to the new state and returns the old one.
	GuiState changeState(GuiState destinationState);
	void changeToStateStyle(GuiState destinationState);

	// creates the default oblong polygon for the button.
	void createPolygon();
public:

	GuiButton();
	GuiButton(
		std::string id, sf::Vector2f pos, sf::Vector2f size,
		std::string guiStyleId,
		std::string text = "",
		EventQueue* mainQ = nullptr
	);

	void setPos(sf::Vector2f pos);
	void setStyleId(std::string newId);

	bool pointInsideBounds(sf::Vector2i point);

	// gui events
	void onMouseEntered();
	void onMouseExited();
	void onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);
	void onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

};