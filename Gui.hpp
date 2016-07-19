#pragma once

#include <map>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "EventHandler.hpp"
#include "EventQueue.hpp"
#include "GuiWidget.hpp"

class Gui : public EventHandler {

private:

	sf::RenderWindow mainWindow;
	EventQueue* mainQ;
	static sf::RenderWindow* mainWinStatic;

public:

	Gui(EventQueue* q);

	void update(const float dt);
	void clear();
	void draw(const float dt);

	void handleEvent(Event* e);

	bool mainWindowIsOpen();
	sf::RenderWindow* getMainWin();

	// GUI OBJECT FUNCTIONS
	static bool Button(float width, float height, float x, float y);
	static void Text(std::string str, float x, float y, const sf::Font& font, unsigned int charSize);

};