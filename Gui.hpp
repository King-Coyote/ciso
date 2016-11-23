#pragma once

#include <unordered_map>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "EventHandler.hpp"
#include "EventQueue.hpp"

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
	static sf::RenderWindow* getMainWin();

};