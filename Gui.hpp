#pragma once

#include <unordered_map>

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
	static std::unordered_map<std::string, GuiWidget> guiObjMap;

public:

	Gui(EventQueue* q);

	void update(const float dt);
	void clear();
	void draw(const float dt);

	void handleEvent(Event* e);

	bool mainWindowIsOpen();
	sf::RenderWindow* getMainWin();

	// GUI OBJECT FUNCTIONS
	static bool Button(float width, float height, float x, float y, std::string id);
	static void Text(std::string str, float x, float y, const sf::Font& font, unsigned int charSize);

};