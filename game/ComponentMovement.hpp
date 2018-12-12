#pragma once

#include <vector>
#include <SFML/System.hpp>

namespace ci {

class TraversableGraph;

class ComponentMovement {
public:
    std::vector<sf::Vector2f> findPath(TraversableGraph* graph, const sf::Vector2f& dest);
private:
    sf::Vector2f pos;
    unsigned areaIndex;
};

}
