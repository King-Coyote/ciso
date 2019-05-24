#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <utility>
#include "SFML/Graphics.hpp"
#include "Thor/Shapes.hpp"
#include "Thor/Math.hpp"
#include "TraversableGraph.hpp"
#include "EventHandler.hpp"
#include <memory>

namespace std {
    template<>
    struct hash<pair<size_t, size_t>> {
        size_t operator() (const pair<size_t, size_t>& n) const {
            return hash<size_t>()(n.first)
            ^ hash<size_t>()(n.second);
        }
    };
}

namespace ci {

class TraversableNode;

// DELETE THIS TRAYSH
typedef std::unique_ptr<sf::Drawable> DPtr;
typedef std::pair<std::size_t, std::size_t> Node;

// struct node_hash {
//     template<class T1, class T2>
//     std::size_t operator() (Node& n) const {
//         return hash<T1>()(n.first) ^ hash<T2>()(n.second);
//     }
// };

bool compareNodes(const NodePtr&, const NodePtr&);

class NavMesh : public EventHandler {
public:
    NavMesh() : EventHandler({EventType::SFML_INPUT}) {}
    NavMesh(std::vector<sf::Vector2f>& pts);
    ~NavMesh();

    void draw(const float dt, sf::RenderWindow& window);

    /**
     * \brief get edge weight between two traversable nodes
     * \return The edge weight, or infinity if there isn't an edge between them
     */
    float getWeightBetween(const Node& a, const Node& b) const;

    /**
     * \brief Return pointers to the neighbours of a node
     */
    std::vector<Node> getNeighbours(const Node& n) const;

        /**
     * \brief Get the nearest node to this one
     */
    const std::pair<std::size_t,std::size_t> getNearestNode(const sf::Vector2f& n) const;

    std::vector<sf::Vector2f> reconstructPath(std::unordered_map<Node, Node>& map, Node& dest);

    // DELETEME
    // void onMouseRelease(EventInput* ei) override;
    sf::Vector2f src;

    vector<sf::Vector2f> findPath(
        const sf::Vector2f& src, 
        const sf::Vector2f& dest
    );

private:
    std::vector<std::vector<bool>> allowedPoints;
    sf::Vector2i size;
    sf::Vector2f position;
    float spacing; // todo name these better eg position instead of offset
    std::vector<DPtr> objs;
    std::vector<sf::Vector2f> vertices; // this is required because thor triangles keep a ref to verts, not a copy
    std::vector<thor::Triangle<sf::Vector2f>> triangles;

    // utility fns
    bool pointInsideMesh(const sf::Vector2f& pt) const;
    sf::Vector2f indicesToPosition(const Node& n) const;
    std::pair<std::size_t, std::size_t> positionToIndices(const sf::Vector2f& pos) const;
};

}