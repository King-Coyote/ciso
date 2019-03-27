#pragma once

#include "SFML/Graphics.hpp"

namespace ci {

class Component {
public:
    Component();
    Component(unsigned level);
    unsigned level;
};

}
