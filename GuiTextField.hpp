#pragma once

#include "GuiObject.hpp"
#include "GuiStyle.hpp"
#include "EventQueue.hpp"

class GuiTextField : public GuiObject, public EventHandler {
	
public: // METHODS

	GuiTextField(
		std::string id,
		sf::Vector2f position,
		sf::Vector2f spriteSize,
		EventQueue* eventQueue,
		std::string styleID = "DEFAULT",
		int textSize = 30,
		std::string defaultString = ""
	);

	void setPos(sf::Vector2f newPos);

	bool pointInsideBounds(sf::Vector2i point);

	// gui events
	void onMouseEntered();
	void onMouseExited();
	void onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);
	void onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton);

	// event handling (note: very separate from gui system events!)
	void handleEvent(std::shared_ptr<Event> e);

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

private: // MEMBERS

	sf::Text text;
	sf::ConvexShape sprite;
	sf::RectangleShape cursorSprite;
	sf::String defaultString;
	EventQueue* eventQueue;
	int textSize;
	sf::Clock cursorClock;
	int cursorPosition;
	bool cursorShown = false;

private: // METHODS

	void blinkCursor();
	void updateCursorPosition(int charIndex);
	int getClickedCharIndex();
	void createPolygon(); // TODO: This is boilerplate code and should be shared somewhere.
	void initialiseVisualElements();
	void changeToStateStyle(GuiState state);

	// incoming events from the eventqueue. I put these under handleEvent for proximity's sake
	void onTextEntered(sf::String textEntered);

	// outgoing event(s)
	void sendEnteredText();

};
