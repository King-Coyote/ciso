#include <iterator>
#include <cmath>
#include <limits>
#include <iostream>
#include "Thor/Math.hpp"
#include "NavMesh.hpp"
#include "TraversableNode.hpp"

using namespace std;

namespace ci {

size_t getIndex(size_t i, size_t j, size_t sizeX) {
    // get the 1d index as if you were using 2d indexing
    return (sizeX * j + i);
}

sf::Vector2f NavMesh::indicesToPosition(const size_t i, const size_t j) const {
    // utility fn to get a position from indices in the navMEsh's allowedpoints collection
}

std::pair<size_t, size_t> NavMesh::positionToIndices(const sf::Vector2f& pos) const {
    return make_pair<size_t, size_t>(
        (size_t)round((pos.x - this->offsetX)/this->spacing),
        (size_t)round((pos.y - this->offsetY)/this->spacing)
    );
}

float sign (sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3)
{
    // this basically tells you how p1 lies in relation to the line formed by p2 and p3
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool pointInTriangle (sf::Vector2f& pt, sf::Vector2f& v1, sf::Vector2f& v2, sf::Vector2f& v3)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

bool compareNodes(const sf::Vector2f& a, const sf::Vector2f& b) {
    // compare lengths of these bois for comparison.
    return (hypot(a.x, a.y) < hypot(b.x, b.y));
}

// DELETEME
// sf::Vector2f findCentroid(sf::Shape& s) {
//     int numPoints = s.getPointCount();
//     sf::Vector2f pointsSum = sf::Vector2f(0.0f, 0.0f);
//     for (int i = 0; i<numPoints; i++) {
//         pointsSum += s.getPoint(i);
//     }
//     pointsSum /= (float)numPoints;
//     return pointsSum;
// }

// DELETEME THIS
sf::CircleShape* createCircle(sf::Vector2f& pos, float r) {
    sf::CircleShape* c = new sf::CircleShape(r);
    c->setPosition(sf::Vector2f(pos.x, pos.y));
    c->setFillColor(sf::Color::Red);
    return c;
}

//DELETEME and THIS
sf::VertexArray* createLine(sf::Vector2f& a, sf::Vector2f& b) {
    sf::VertexArray* line = new sf::VertexArray(sf::LineStrip, 2);
    (*line)[0].position = sf::Vector2f(a.x+5.0f, a.y+5.0f);
    (*line)[0].color = sf::Color::Red;
    (*line)[1].position = sf::Vector2f(b.x+5.0f, b.y+5.0f);
    (*line)[1].color = sf::Color::Red;
    return line;
}

NavMesh::NavMesh(std::vector<sf::Vector2f>& pts) :
    adjacencies(map<sf::Vector2f, std::vector<Edge>, MapComparator>(&compareNodes))
{
    float scaleFactor = 4.5f;
    float ox = -200.0f;
    float oy = -300.0f;
    float minY = numeric_limits<float>::infinity();
    float minX = numeric_limits<float>::infinity();
    float maxY = 0.0f;
    float maxX = 0.0f;
    for (auto& pt : pts) {
        pt.x = pt.x*scaleFactor;
        pt.y = pt.y*scaleFactor;
        pt.x += ox;
        pt.y += oy;
        if (pt.x < minX) minX = pt.x;
        if (pt.y < minY) minY = pt.y;
        if (pt.x > maxX) maxX = pt.x;
        if (pt.y > maxY) maxY = pt.y;
    }
    const size_t rangeX = maxX - minX;
    const size_t rangeY = maxY - minY;
    const size_t pointRange = rangeX * rangeY;
    this->spacing = 5.0f;
    this->allowedPoints = vector<vector<bool>>(rangeY, vector<bool>(rangeX));
    vector<thor::Triangle<sf::Vector2f>> tris;
    thor::triangulatePolygon(
        pts.begin(), pts.end(),
        back_inserter(tris)
    );
    for (auto& tri : tris) {
        sf::ConvexShape* triShape = new sf::ConvexShape(3);
        triShape->setPoint(0, tri[0]);
        triShape->setPoint(1, tri[1]);
        triShape->setPoint(2, tri[2]);
        triShape->setFillColor(sf::Color::Cyan);
        triShape->setOutlineColor(sf::Color::Blue);
        triShape->setOutlineThickness(2.0f);
        this->objs.push_back(unique_ptr<sf::Drawable>(triShape));
    }
    for (size_t j = 0; j < rangeY; ++j) {
        for (size_t i = 0; i < rangeX; ++i) {
            sf::Vector2f pos = sf::Vector2f(minX + (i*spacing), minY + (j*spacing));
            for (auto& tri : tris) {
                if (pointInTriangle(pos, tri[0], tri[1], tri[2])) {
                    this->allowedPoints[i][j] = true;
                    this->objs.push_back(unique_ptr<sf::Drawable>(createCircle(pos, 2.5f)));
                }
            }
        }
    }
    cout << "completed navmesh gen" << endl;
}

NavMesh::~NavMesh(){}

void NavMesh::draw(const float dt, sf::RenderWindow& window) {
    for (auto& o : this->objs) {
        window.draw(*o);
    }
}

float NavMesh::getWeightBetween(const sf::Vector2f& a, const sf::Vector2f& b) const {
    return 0.0f;
}

std::vector<const sf::Vector2f> NavMesh::getNeighbours(const sf::Vector2f& n) {
    auto indices = this->positionToIndices(n);
    size_t sizeX = this->allowedPoints[0].size(); // should all be same size
    size_t sizeY = this->allowedPoints.size();
    vector<const sf::Vector2f> neighbours;
    for (int j = -1; j<2; ++j) {
        int cardY = indices.second - j;
        for (int i = -1; i<2; ++i) {
            int cardX = indices.first + i;
            if (cardX >= 0 && cardX < sizeX
            && cardY >= 0 && cardY < sizeY
            && this->allowedPoints[cardX][cardY]) {
                neighbours.push_back(indicesToPosition(cardX, cardY));
            }
        }
    }
    return neighbours;
}

const sf::Vector2f NavMesh::getNearestNode(const sf::Vector2f& n) const {
    return sf::Vector2f();
}

void NavMesh::addNode(sf::Vector2f& n) {
    
}

void NavMesh::addEdge(sf::Vector2f& a, sf::Vector2f& b) {
    if (this->adjacencies.count(a) == 0) {
        this->adjacencies[a] = vector<ci::Edge>();
    }
    if (this->adjacencies.count(b) == 0) {
        this->adjacencies[b] = vector<ci::Edge>();
    }
    sf::Vector2f diff = a - b;
    float dist = hypot(diff.x, diff.y);
    this->adjacencies[a].push_back(ci::Edge(&b, dist));
    this->adjacencies[b].push_back(ci::Edge(&a, dist));
}



}