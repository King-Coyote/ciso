#pragma once

#include <vector>
#include <SFML/System.hpp>
#include "TraversableGraph.hpp"

namespace ci {

class ComponentMovement {
public:
    std::vector<sf::Vector2f> findPath(TraversableGraph<sf::Vector2f>* graph, const sf::Vector2f& dest);
private:
    sf::Vector2f pos;
    unsigned areaIndex;
};

}
