#pragma once

#include "GuiObject.hpp"
#include "EventQueue.hpp"
#include "SFML\Graphics.hpp"
#include "GuiStyle.hpp"

// Button class for the gui system. Obvis. Created using a CREATE_GUI event.
class GuiButton : public GuiObject, public EventHandler {

public: // METHODS

	GuiButton(
		std::string id, sf::Vector2f pos, sf::Vector2f size,
		std::string guiStyleId,
		EventQueue& incomingEventQueue, // events it needs to actually function
		EventQueue* outgoingEventQueue, // optional, events that can be going out of the button. can be same as above
		std::string textString = ""
	);

	void setPos(sf::Vector2f pos);
	void setStyleId(std::string newId);

	bool pointInsideBounds(sf::Vector2i point);

	// gui events
	void onMouseEntered();
	void onMouseExited();

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

protected: // METHODS

	// EVENTS
	void onMouseButtonPressed(sf::Vector2i mousePos, sf::Mouse::Button button);
	void onMouseButtonReleased(sf::Vector2i mousePos, sf::Mouse::Button button);

private: // MEMBERS

	std::string textString;
	sf::Text text;
	sf::ConvexShape sprite;
	// queue for events going out of the button
	EventQueue* outgoingEventQueue;

private: // METHODS

	// creates the default oblong polygon for the button.
	void createPolygon();
	// sets text according to justification etc.
	// TODO needs to have justification lmao
	void setTextPosition();
	void initialiseVisualElements();
	void changeToStateStyle(GuiState state);

};