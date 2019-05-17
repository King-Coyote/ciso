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
	EventHandler() = delete;
	EventHandler(std::vector<EventType>);
	virtual ~EventHandler();

	void handleEvent(Event* e);

protected:
	virtual void onMousePress(EventInput* ei) {}
	virtual void onMouseRelease(EventInput* ei) {}
	virtual void onMouseMove(EventInput* ei) {}
	virtual void onCreateGui(const EventCreateGui* cgep) {}
	virtual void onGuiButtonClicked(const EventGuiButtonClicked* egbc) {}
	virtual void onTextEntered(EventInput* ei) {}
	virtual void onKeyPressed(EventInput* ei) {}
	virtual void onKeyReleased(EventInput* ei) {}
	virtual void onRunScript(EventRunScript* ers) {}

private:
	std::vector<EventType> types;

};

}