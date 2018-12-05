#include <iterator>
#include "Thor/Math.hpp"
#include "NavMesh.hpp"

using namespace std;

namespace ci {
NavMesh::NavMesh(std::vector<sf::Vector2f>& pts) {
    vector<thor::Triangle<sf::Vector2f>> tris;
    thor::triangulate(
        pts.begin(), pts.end(),
        back_inserter(tris)
    );
    for (auto& tri : tris) {
        sf::ConvexShape triShape = sf::ConvexShape(3);
        triShape.setPoint(0, tri[0]);
        triShape.setPoint(1, tri[1]);
        triShape.setPoint(2, tri[2]);
        triShape.setFillColor(sf::Color::Cyan);
        triShape.setOutlineColor(sf::Color::Blue);
        triShape.setOutlineThickness(2.0f);
        this->triangles.push_back(triShape);
    }
}

void NavMesh::draw(const float dt, sf::RenderWindow& window) {
    for (auto& tri : this->triangles) {
        window.draw(tri);
    }
}

}