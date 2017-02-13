#pragma once

#include "GuiObject.hpp"
#include "GuiStyle.hpp"
#include "EventQueue.hpp"

class GuiTextField : public GuiObject {
	
public: // METHODS

	GuiTextField(
		std::string id,
		sf::Vector2f position,
		sf::Vector2f spriteSize,
		EventQueue* eventQueue,
		int textSize = 30,
		std::string defaultText = ""
	);

	// gui events
	void onMouseEntered();
	void onMouseExited();
	void onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);
	void onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

private: // MEMBERS

	sf::Text text;
	sf::ConvexShape sprite;
	EventQueue* eventQueue;
	std::string textString;
	int textSize;
	sf::Clock cursorClock;
	int cursorPosition;
	bool cursorShown = false;

private: // METHODS

	void blinkCursor();
	void createPolygon(); // TODO: This is boilerplate code and should be shared somewhere.
	void initialiseVisualElements();
	void changeToStateStyle(GuiState state);

};
