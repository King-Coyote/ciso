#pragma once

#include <vector>
#include <SFML/System.hpp>
#include "luavm/Table.hpp"
#include "Component.hpp"
#include "TraversableGraph.hpp"

namespace ci {

class ComponentMovement : public Component {
public:
    ComponentMovement();
    ComponentMovement(mun::Table& t);
    ComponentMovement(mun::Table&& t);

    std::vector<sf::Vector2f> findPath(TraversableGraph<sf::Vector2f>* graph, const sf::Vector2f& dest);
private:
    sf::Vector2f pos;
    unsigned areaIndex;
};

}
