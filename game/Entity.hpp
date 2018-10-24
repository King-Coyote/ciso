#pragma once

#include "SFML/Graphics.hpp"

namespace ci {

class Entity {
public:
    void update(float dt);
private:
    bool instanced = false;
};

}