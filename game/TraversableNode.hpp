#pragma once
#include <queue>
#include <vector>
#include "SFML/System.hpp"

namespace ci {

// bool compareNodes(const TraversableNode* a, const TraversableNode* b) {
//     return false;
// }

// typedef std::priority_queue<
//     TraversableNode*, 
//     std::vector<TraversableNode*>
// > nodeQueue;
// typedef typename nodeQueue::container_type::const_iterator node_const_iterator;

// class NodeQueue : public nodeQueue {
// public:
//     node_const_iterator find(const TraversableNode& val) const;
// };

class TraversableNode {
public:
    const sf::Vector2f getPos() const;
    const std::vector<TraversableNode*>& getNeighbours() const;
private:
    sf::Vector2f worldPos;
    std::vector<TraversableNode*> neighbours;

};

}
