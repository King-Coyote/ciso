#pragma once

#include <memory>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class GuiObject;

using namespace std;

namespace ci {

enum class EventType {
    SFML_INPUT,
    CREATE_GUI,
        GUI_BUTTONCLICKED,
        GUI_TEXTENTERED
};

struct Event {
    Event(EventType type);
    ~Event() {}
    EventType type;
    union {
        sf::Event sfmlEvent; // SFML_INPUT
        sf::Vector2i mousePos;
    };
    // generic string that all events can have
    string str;
};

}