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
    virtual ~TraversableNode(){}
};

class DestinationNode : public TraversableNode {
public:
    sf::Vector2f getPos() const {return sf::Vector2f();}
private:
    sf::Vector2f pos;
};

}
