#pragma once

#include <string>

enum class EventType {VOID,DEBUG,INPUT};

class Event {

public:

	EventType type;

	Event(EventType type) : type(type) {}
	Event() : type(EventType::VOID) {}
	// virtual destructor for polymorphism
	virtual ~Event(){};

};

class EventInput : public Event {

public:

	int mouseX;
	int mouseY;

	EventInput(int x, int y) {
		type = EventType::INPUT;
		mouseX = x;
		mouseY = y;
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