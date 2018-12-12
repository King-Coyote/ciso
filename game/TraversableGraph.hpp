#pragma once

#include <vector>
#include <map>
#include "SFML/System.hpp"

namespace ci {

class TraversableNode;

class TraversableGraph {
public:
    /**
     * /brief Gets the node nearest to a position.
     * /param pos the position to get nearest node to
     * /return A pointer to the nearest node; nullptr if the node list was empty.
     */
    TraversableNode* getNearestNode(const sf::Vector2f& pos) const;

    /**
     * \brief get edge weight between two traversable nodes
     * \return The edge weight, or infinity if there isn't an edge between them
     */
    float getWeightBetween(TraversableNode* a, TraversableNode* b) const;

private:
    std::vector<TraversableNode*> nodes;
    // This is symmetric, so that getWeightBetween's order does not matter
    std::map<std::pair<TraversableNode*, TraversableNode*>, float> adjacencies;

};

}
