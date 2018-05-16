#pragma once

#include <vector>
#include <memory>

#include "SFML/System.hpp"

class Event;
class EventQueue;
class GuiObject;
enum class EventType;

using namespace std;

class EventHandler {

public:
	EventHandler() {}
	EventHandler(EventQueue&, std::vector<EventType>);
	virtual ~EventHandler() {};

	virtual void handleEvent(const Event& e) {}

protected:
	virtual void onLeftClick(sf::Vector2f& mousePos) {}
	virtual void onRightClick(sf::Vector2f& mousePos) {}

};