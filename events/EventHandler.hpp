#pragma once

#include <vector>
#include <memory>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Event.hpp"

using namespace std;

namespace ci {

class EventQueue;
class GuiObject;

class EventHandler {

public:
	EventHandler() {}
	EventHandler(EventQueue&, std::vector<EventType>);
	virtual ~EventHandler() {};

	void handleEvent(Event* e);

protected:
	virtual void onMousePress(const sf::Event& e) {}
	virtual void onMouseRelease(const sf::Event& e) {}
	virtual void onMouseMove(const sf::Event& e) {}
	virtual void onCreateGui(const EventCreateGui* cgep) {}
	virtual void onGuiButtonClicked(const EventGuiButtonClicked* egbc) {}

};

}