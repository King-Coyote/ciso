#pragma once

#include <string>
#include <iostream>
#include <memory>

#include "Graphics.hpp"
#include "GuiObject.hpp"

enum class EventType {
	VOID,
	DEBUG,
	INPUT,
	CREATE_GUI, CREATE_GUI_LIST,
	GUI_BUTTONCLICKED, GUI_TEXTENTERED
};

class Event {

protected:
	static unsigned int count;

public:
	EventType type;
	unsigned int id;

	Event(EventType type) : type(type) {}
	Event() : type(EventType::VOID), id(count) { Event::count++; }
	std::string getId() { return std::to_string(id); }
	// virtual destructor for dat polymorphisms
	virtual ~Event(){};

};

class EventCreateGui : public Event {
private:
	std::shared_ptr<GuiObject> m_guiObj;
public:
	EventCreateGui(GuiObject* guiObj);
	std::shared_ptr<GuiObject> getGuiObj();
};

// creates a bunch of gui objects from a list.
class EventCreateGuiList : public Event {
private:
	std::shared_ptr<std::vector<GuiObject>> m_guiObjList;
public:
	EventCreateGuiList(std::vector<GuiObject>* guiObjList);
	std::shared_ptr<std::vector<GuiObject>> getGuiObjList();
};

class EventGuiButtonClicked : public Event {
private:
	std::string buttonId;
	sf::Vector2i mousePos;
public:
	EventGuiButtonClicked(std::string id, sf::Vector2i mousePos);
	std::string getButtonId();
	sf::Vector2i getMousePos();
};

class EventGuiTextEntered : public Event {
private:
	std::string m_id;
	sf::String textEntered;
public:
	EventGuiTextEntered(std::string id, sf::String textEntered);
	std::string getId();
	sf::String getTextEntered();
};

class EventSfmlInput : public Event {

private:

	sf::Event sfEvent;

public:

	EventSfmlInput(sf::Event sfe);

	sf::Event* getEventPtr();

};

class EventInputButton : public Event {

public:

	int mouseX;
	int mouseY;

	EventInputButton(int state) {// some button identifier here
		type = EventType::INPUT;
	}

};

class EventDebug : public Event {

private:

	std::string msg;
	int level;

public:

	EventDebug(std::string msg, int level) {
		type = EventType::DEBUG;
		this->msg = msg;
		this->level = level;
	}

	std::string getMsg();
	int getLevel();

};