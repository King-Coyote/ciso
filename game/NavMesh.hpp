#pragma once

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Thor/Shapes.hpp"
#include "TraversableGraph.hpp"

namespace ci {

class TraversableNode;

typedef std::pair<sf::Vector2f*, float> Edge;
typedef bool (*MapComparator)(const sf::Vector2f&, const sf::Vector2f&);
typedef std::map<sf::Vector2f, std::vector<Edge>, MapComparator> AdjacencyMap;
// DELETE THIS TRAYSH
typedef std::shared_ptr<sf::Drawable> DPtr;

bool compareNodes(const NodePtr&, const NodePtr&);

class NavMesh : public TraversableGraph<sf::Vector2f> {
public:
    NavMesh() {}
    NavMesh(std::vector<sf::Vector2f>& pts);
    ~NavMesh();

    void draw(const float dt, sf::RenderWindow& window);

    /**
     * \brief get edge weight between two traversable nodes
     * \return The edge weight, or infinity if there isn't an edge between them
     */
    float getWeightBetween(const sf::Vector2f& a, const sf::Vector2f& b) const override;

    /**
     * \brief Return pointers to the neighbours of a node
     */
    std::vector<const sf::Vector2f*> getNeighbours(const sf::Vector2f& n) override;

        /**
     * \brief Get the nearest node to this one
     */
    virtual const sf::Vector2f* getNearestNode(const sf::Vector2f& n) const override;

    void addNode(sf::Vector2f& n) override;
    void addEdge(sf::Vector2f& a, sf::Vector2f& b) override;

private:
    std::vector<DPtr> objs;
    ci::AdjacencyMap adjacencies;
};

}