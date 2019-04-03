#pragma once

#include "luavm/Table.hpp"
#include "Component.hpp"

namespace ci {

class ComponentTransform : public Component {
public:
    ComponentTransform();
    ComponentTransform(mun::Table& t);
    ComponentTransform(mun::Table&& t);

    sf::Vector2f pos;
    unsigned r; // rotation cardinal: 0 for straight up, then 1 for NE, 2 for E, so on.
};

}
