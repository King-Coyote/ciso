#pragma once

#include <memory>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class GuiObject;

using namespace std;

enum class EventType {
    SFML_INPUT,
    CREATE_GUI,
        GUI_BUTTONCLICKED,
        GUI_TEXTENTERED
};

struct Event {
    Event(EventType type);
    ~Event() {}
    // primary data
    EventType type;
    union {
        sf::Event sfmlEvent; // SFML_INPUT
        sf::Vector2i mousePos;
        GuiObject* guiObject; // CREATE_GUI
    };
    // generic string that all events can have
    string str;
};