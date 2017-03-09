#pragma once

#include <vector>
#include <memory>

#include "Event.hpp"

class EventQueue;

class EventHandler {

public:

	EventHandler() {}
	EventHandler(EventQueue&, std::vector<EventType>);

	virtual ~EventHandler() {};

	virtual void handleEvent(std::shared_ptr<Event> e);

protected:
	/*
	VOID,
	DEBUG,
	INPUT,
	CREATE_GUI, CREATE_GUI_LIST,
	GUI_BUTTONCLICKED, GUI_TEXTENTERED
	*/
	virtual void onDebug(std::string msg, int level) {}
	virtual void onCreateGui(std::shared_ptr<GuiObject> guiObj) {}
	virtual void onCreateGuiList(std::shared_ptr<std::vector<GuiObject>> guiObjList) {}
	virtual void onGuiButtonClicked(std::string id, sf::Vector2i mousePos) {}
	virtual void onGuiTextFieldEntered(std::string id, sf::String textEntered) {}
	// INPUT EVENTS in caps bcuz there they're own thing ay lol
	virtual void onMouseButtonPressed(sf::Vector2i mousePos, sf::Mouse::Button button) {}
	virtual void onMouseButtonReleased(sf::Vector2i mousePos, sf::Mouse::Button button) {}
	virtual void onKeyPressed(sf::Keyboard::Key keyCode) {}
	virtual void onTextEntered(sf::Uint32 textEntered) {}

};