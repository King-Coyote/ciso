#pragma once

#include <vector>
#include <memory>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace std;

namespace ci {

class Event;
class EventQueue;
class GuiObject;
enum class EventType;

class EventHandler {

public:
	EventHandler() {}
	EventHandler(EventQueue&, std::vector<EventType>);
	virtual ~EventHandler() {};

	void handleEvent(const Event& e);

protected:
	virtual void onMousePress(const sf::Event& e) {}
	virtual void onMouseRelease(const sf::Event& e) {}
	virtual void onMouseMove(const sf::Event& e) {}
	virtual void onCreateGui(const std::string& filename) {}

};

}