#pragma once

#include <string>
#include <iostream>
#include <memory>

#include "SFML\Graphics.hpp"
#include "GuiObject.hpp"

enum class EventType {VOID,
					DEBUG,
					INPUT,
					CREATE_GUI};

class Event {

protected:
	static unsigned int count;

public:
	EventType type;
	unsigned int id;

	Event(EventType type) : type(type) {}
	Event() : type(EventType::VOID), id(count) { Event::count++; }
	std::string getIdStr() { return std::to_string(id); }
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