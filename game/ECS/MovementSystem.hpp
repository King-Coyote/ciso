#pragma once

#include <vector>
#include "SFML/System.hpp"
#include "ComponentTransform.hpp"
#include "TraversableGraph.hpp"

namespace ci {

class MovementSystem {
public:
    void update(float dt);
private:
    std::vector<sf::Vector2f> findPath(TraversableGraph<sf::Vector2f>* graph, const sf::Vector2f& dest);
    std::vector<ComponentTransform>& transforms;

};

}
