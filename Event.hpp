#pragma once

#include <string>
#include <iostream>

#include "SFML\Graphics.hpp"

enum class EventType {VOID,
					DEBUG,
					INPUT};

class Event {

protected:

	static unsigned int count;

public:

	EventType type;
	unsigned int id;

	Event(EventType type) : type(type) {}
	Event() : type(EventType::VOID), id(count) { Event::count++; }
	std::string getIdStr() { return std::to_string(id); }
	// virtual destructor for polymorphism
	virtual ~Event(){};

};

class EventSfmlInput : public Event {

private:

	sf::Event sfEvent;

public:

	EventSfmlInput(sf::Event sfe) {
		type = EventType::INPUT;
		sfEvent = sfe;
	}

	sf::Event::EventType getSfmlType() { return sfEvent.type; }

	//DELETEME
	~EventSfmlInput() { std::cout << "SFML EVENT " << this->getIdStr() << "DESTROYED\n"; }

};

class EventInputMouseClick : public Event {

public:

	int mouseX;
	int mouseY;

	EventInputMouseClick(int x, int y) {
		type = EventType::INPUT;
		mouseX = x;
		mouseY = y;
	}

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