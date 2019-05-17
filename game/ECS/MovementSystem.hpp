#pragma once

#include <vector>
#include "SFML/System.hpp"
#include "EventHandler.hpp"

namespace ci {

class MovementSystem : public EventHandler {
public:
    MovementSystem();
    void update(float dt);
    
    // Event handlers
private:

};

}