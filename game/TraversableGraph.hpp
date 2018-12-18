#pragma once

#include <vector>
#include <map>
#include "SFML/System.hpp"

namespace ci {

class TraversableNode;

typedef std::unique_ptr<TraversableNode> NodePtr;

class TraversableGraph {
public:
    virtual ~TraversableGraph(){}
    // /**
    //  * /brief Gets the node nearest to a position.
    //  * /param pos the position to get nearest node to
    //  * /return A pointer to the nearest node; nullptr if the node list was empty.
    //  */
    // TraversableNode* getNearestNode(const sf::Vector2f& pos) const;

    /**
     * \brief get edge weight between two traversable nodes
     * \return The edge weight, or infinity if there isn't an edge between them
     */
    virtual float getWeightBetween(TraversableNode* a, TraversableNode* b) const = 0;

    /**
     * \brief Return pointers to the neighbours of a node
     */
    virtual std::vector<TraversableNode*> getNeighbours(const TraversableNode& n) = 0;

    virtual void addNode(TraversableNode* n) = 0;
    virtual void addNode(NodePtr& n) = 0;
    virtual void addEdge(TraversableNode* a, TraversableNode* b) = 0;
    virtual void addEdge(NodePtr& a, NodePtr& b) = 0;

private:
    // std::vector<NodePtr> nodes;
    // // This is symmetric, so that getWeightBetween's order does not matter
    // std::map<std::pair<sf::Vector2f, NodePtr>, float> adjacencies;

};

}
