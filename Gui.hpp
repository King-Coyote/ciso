#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "EventHandler.hpp"
#include "EventQueue.hpp"

class Gui : public EventHandler {

private:

	sf::RenderWindow mainWindow;
	EventQueue* mainQ;

public:

	Gui(EventQueue* q);

	void update(const float dt);
	void draw(const float dt);

	void handleEvent(const Event& e);

	bool mainWindowIsOpen();
	sf::RenderWindow* getMainWin();

};