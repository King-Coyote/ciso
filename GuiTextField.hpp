#pragma once

class GuiObject;
class GuiStyle;
class EventQueue;

class GuiTextField : public GuiObject, public EventHandler {
	
public: // METHODS

	GuiTextField(
		std::string id,
		sf::Vector2f position,
		sf::Vector2f spriteSize,
		EventQueue& incomingEventQueue,
		EventQueue* outgoingEventQueue,
		std::string styleID = "DEFAULT",
		int textSize = 30,
		std::string defaultString = ""
	);

	void setPos(sf::Vector2f newPos);

	bool pointInsideBounds(sf::Vector2i point);

	// gui events
	void onMouseEntered();
	void onMouseExited();
	
	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

protected: //METHODS

	// EVENTS
	void onMouseButtonPressed(sf::Vector2i mousePos, sf::Mouse::Button button);
	void onMouseButtonReleased(sf::Vector2i mousePos, sf::Mouse::Button button);

private: // DATA STRUCTURES N CLASSES

	// for finding the char you clicked on and the position the cursor should be in
	struct CharIndexAndCursorPosition {
		int charIndex;
		sf::Vector2f cursorPosition;
		CharIndexAndCursorPosition(int index, sf::Vector2f position) :
			charIndex(index), cursorPosition(position) {}
	};

private: // MEMBERS

	sf::Text text;
	sf::ConvexShape sprite;
	sf::RectangleShape cursorSprite;
	sf::String defaultString;
	EventQueue& incomingEventQueue;
	EventQueue* outgoingEventQueue;
	int textSize;
	sf::Clock cursorClock;
	// this is the index of the cursor - note that this is the char that the cursor is to the LEFT of
	int cursorPosition;
	bool cursorShown = false;

private: // METHODS

	void blinkCursor();
	void updateCursorPosition(unsigned int charIndex);
	// returns the index of the char under the mouse pointer
	int getClickedCharIndex(sf::Vector2i mousePos);
	void createPolygon(); // TODO: This is boilerplate code and should be shared somewhere.
	void initialiseVisualElements();
	void changeToStateStyle(GuiState state);

	// incoming events from the eventqueue. I put these under handleEvent for proximity's sake
	void onTextEntered(sf::Uint32 textEntered);
	void onKeyPressed(sf::Keyboard::Key keyPressed);

	void deleteTextAtIndex(int index);

	// outgoing event(s)
	void sendEnteredText();

};
