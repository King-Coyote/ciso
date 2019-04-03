#pragma once

#include "SFML/Graphics.hpp"

namespace ci {

class Component {
public:
    Component();
    Component(int level);
    int level;
};

}
