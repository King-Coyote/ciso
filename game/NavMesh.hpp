#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "Thor/Shapes.hpp"
#include "TraversableGraph.hpp"

namespace ci {

class TraversableNode;

typedef std::pair<TraversableNode*, float> Edge;
typedef bool (*MapComparator)(const TraversableNode*&, const TraversableNode*&);

bool compareNodes(const NodePtr&, const NodePtr&);

class NavMesh : public TraversableGraph {
public:
    NavMesh() {}
    NavMesh(std::vector<sf::Vector2f>& pts);

    void draw(const float dt, sf::RenderWindow& window);

    /**
     * \brief get edge weight between two traversable nodes
     * \return The edge weight, or infinity if there isn't an edge between them
     */
    float getWeightBetween(TraversableNode* a, TraversableNode* b) const override;

    void addNode(TraversableNode* n) override;
    void addNode(NodePtr& n) override;
    void addEdge(TraversableNode* a, TraversableNode* b) override;
    void addEdge(NodePtr& a, NodePtr& b) override;

private:
    std::vector<std::unique_ptr<sf::Drawable>> objs;
    std::vector<NodePtr> nodes;
    std::map<TraversableNode*, std::vector<Edge>, MapComparator> adjacencies;
};

}