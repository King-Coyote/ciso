#pragma once

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Thor/Shapes.hpp"
#include "TraversableGraph.hpp"
#include <memory>

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
    std::vector<const sf::Vector2f> getNeighbours(const sf::Vector2f& n) override;

        /**
     * \brief Get the nearest node to this one
     */
    virtual const sf::Vector2f getNearestNode(const sf::Vector2f& n) const override;

    void addNode(sf::Vector2f& n) override;
    void addEdge(sf::Vector2f& a, sf::Vector2f& b) override;

private:
    std::vector<std::vector<bool>> allowedPoints;
    float spacing, offsetX, offsetY; // todo name these better eg position instead of offset
    std::vector<DPtr> objs;
    ci::AdjacencyMap adjacencies;

    // utility fns to get indices from position and vice versa
    sf::Vector2f indicesToPosition(const size_t i, const size_t j) const;
    std::pair<size_t, size_t> positionToIndices(const sf::Vector2f& pos) const;
};

}