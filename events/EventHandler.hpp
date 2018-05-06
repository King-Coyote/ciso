#pragma once

#include <vector>
#include <memory>

#include "System.hpp"
#include "Window.hpp"

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

};