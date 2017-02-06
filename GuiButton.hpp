#pragma once

#include "GuiObject.hpp"
#include "EventQueue.hpp"
#include "SFML\Graphics.hpp"
#include "GuiStyle.hpp"

// Button class for the gui system. Obvis. Created using a CREATE_GUI event.
class GuiButton : public GuiObject {

public: // METHODS

	GuiButton(
		std::string id, sf::Vector2f pos, sf::Vector2f size,
		std::string guiStyleId,
		std::string textString = "",
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

private: // MEMBERS

	std::string textString;
	sf::Text text;
	sf::ConvexShape sprite;
	// main event queue, if any
	EventQueue* mainQ;

private: // METHODS

	// creates the default oblong polygon for the button.
	void createPolygon();
	// sets text according to justification etc.
	// TODO needs to have justification lmao
	void setTextPosition();
	void initialiseVisualElements();
	void changeToStateStyle(GuiState state);

};