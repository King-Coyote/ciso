#pragma once

#include <memory>
#include <string>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class GuiObject;

namespace ci {

enum class EventType {
    SFML_INPUT,
    CREATE_GUI,
        GUI_BUTTONCLICKED,
        GUI_TEXTENTERED
};

class Event {
public:
    Event(EventType type) :
        type(type) {}
    virtual ~Event() {}

    const EventType getType() const {
        return type;
    }
private:
    EventType type;
};

class EventInput : public Event {
public:
    EventInput(sf::Event sfEvent) : 
        Event(EventType::SFML_INPUT),
        sfEvent(sfEvent),
        captured(false) {}

    void capture() {
        captured = true;
    }

    const bool isCaptured() const {
        return captured;
    }
    
    const sf::Event sfEvent;
private:
    bool captured;
};

class EventCreateGui : public Event {
public:
    EventCreateGui(std::string filename) :
        Event(EventType::CREATE_GUI),
        filename(filename) {}

    const std::string filename;
};

class EventGuiButtonClicked : public Event {
public:
    EventGuiButtonClicked(std::string id) :
        Event(EventType::GUI_BUTTONCLICKED),
        id(id) {}

    const std::string id;
};


}