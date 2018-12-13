#include <iterator>
#include "Thor/Math.hpp"
#include "NavMesh.hpp"

using namespace std;

namespace ci {

sf::Vector2f findCentroid(sf::Shape& s) {
    int numPoints = s.getPointCount();
    sf::Vector2f pointsSum = sf::Vector2f(0.0f, 0.0f);
    for (int i = 0; i<numPoints; i++) {
        pointsSum += s.getPoint(i);
    }
    pointsSum /= (float)numPoints;
    return pointsSum;
}

NavMesh::NavMesh(std::vector<sf::Vector2f>& pts) {
    vector<thor::Triangle<sf::Vector2f>> tris;
    thor::triangulate(
        pts.begin(), pts.end(),
        back_inserter(tris)
    );
    for (auto& tri : tris) {
        sf::ConvexShape* triShape = new sf::ConvexShape(3);
        float chance = ((float)(rand())/RAND_MAX);
        if (chance < 0.2f) {
            continue;
        }
        triShape->setPoint(0, tri[0]);
        triShape->setPoint(1, tri[1]);
        triShape->setPoint(2, tri[2]);
        triShape->setFillColor(sf::Color::Cyan);
        triShape->setOutlineColor(sf::Color::Blue);
        triShape->setOutlineThickness(2.0f);
        this->objs.push_back(unique_ptr<sf::Drawable>(triShape));
        unique_ptr<sf::CircleShape> centroidShape = unique_ptr<sf::CircleShape>(new sf::CircleShape(4.0f));
        centroidShape->setFillColor(sf::Color::Red);
        centroidShape->setPosition(findCentroid(*triShape));
        this->objs.push_back(std::move(centroidShape));
    }
}

void NavMesh::draw(const float dt, sf::RenderWindow& window) {
    for (auto& o : this->objs) {
        window.draw(*o);
    }
}

}