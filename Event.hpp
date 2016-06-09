#pragma once

#include <string>

enum class EventType {VOID,
					DEBUG,
					INPUT_MCLICK, INPUT_BUTTON};

class Event {

public:

	EventType type;

	Event(EventType type) : type(type) {}
	Event() : type(EventType::VOID) {}
	// virtual destructor for polymorphism
	virtual ~Event(){};

};

class EventInputMouseClick : public Event {

public:

	int mouseX;
	int mouseY;

	EventInputMouseClick(int x, int y) {
		type = EventType::INPUT_MCLICK;
		mouseX = x;
		mouseY = y;
	}

};

class EventInputButton : public Event {

public:

	int mouseX;
	int mouseY;

	EventInputButton(int state) {// some button identifier here
		type = EventType::INPUT_BUTTON;
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