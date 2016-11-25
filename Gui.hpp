#pragma once

#include <vector>
#include <memory>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "EventHandler.hpp"
#include "EventQueue.hpp"
#include "GuiObject.hpp"

class Gui : public EventHandler {

private:

	sf::RenderWindow& mainWindow;
	EventQueue& mainQ;

public:

	Gui(EventQueue& q, sf::RenderWindow& mainWindow);

	void update(const float dt);
	void clear();
	void draw(const float dt);

	void handleEvent(std::shared_ptr<Event> e);

	bool mainWindowIsOpen();

};