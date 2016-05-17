#pragma once

enum class EventType {VOID,DEBUG,INPUT};

class Event {

public:

	EventType type;

	Event(EventType type) : type(type) {}
	Event() : type(EventType::VOID) {}

};

class InputEvent : public Event {

public:

	int mouseX;
	int mouseY;

	InputEvent(int x, int y) {
		type = EventType::INPUT;
		mouseX = x;
		mouseY = y;
	}

};