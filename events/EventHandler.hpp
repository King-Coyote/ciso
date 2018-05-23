#pragma once

#include <vector>
#include <memory>

#include "SFML/System.hpp"

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
	virtual void onLeftClick(const sf::Vector2f& mousePos) {}
	virtual void onRightClick(const sf::Vector2f& mousePos) {}
	virtual void onCreateGui(const std::string& filename) {}

};

}