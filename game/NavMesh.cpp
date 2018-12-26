#include <iterator>
#include <cmath>
#include "Thor/Math.hpp"
#include "NavMesh.hpp"
#include "TraversableNode.hpp"

using namespace std;

namespace ci {

bool compareNodes(const sf::Vector2f& a, const sf::Vector2f& b) {
    // compare lengths of these bois for comparison.
    return (hypot(a.x, a.y) < hypot(b.x, b.y));
}

sf::Vector2f findCentroid(sf::Shape& s) {
    int numPoints = s.getPointCount();
    sf::Vector2f pointsSum = sf::Vector2f(0.0f, 0.0f);
    for (int i = 0; i<numPoints; i++) {
        pointsSum += s.getPoint(i);
    }
    pointsSum /= (float)numPoints;
    return pointsSum;
}

// DELETEME THIS
sf::CircleShape* createCircle(sf::Vector2f& pos) {
    sf::CircleShape* c = new sf::CircleShape(5.0f);
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
    // vector<thor::Triangle<sf::Vector2f>> tris;
    // thor::triangulate(
    //     pts.begin(), pts.end(),
    //     back_inserter(tris)
    // );
    // for (auto& tri : tris) {
    //     sf::ConvexShape* triShape = new sf::ConvexShape(3);
    //     float chance = ((float)(rand())/RAND_MAX);
    //     if (chance < 0.2f) {
    //         continue;
    //     }
    //     triShape->setPoint(0, tri[0]);
    //     triShape->setPoint(1, tri[1]);
    //     triShape->setPoint(2, tri[2]);
    //     triShape->setFillColor(sf::Color::Cyan);
    //     triShape->setOutlineColor(sf::Color::Blue);
    //     triShape->setOutlineThickness(2.0f);
    //     this->objs.push_back(unique_ptr<sf::Drawable>(triShape));
    //     unique_ptr<sf::CircleShape> centroidShape = unique_ptr<sf::CircleShape>(new sf::CircleShape(4.0f));
    //     centroidShape->setFillColor(sf::Color::Red);
    //     sf::Vector2f cPos = findCentroid(*triShape);
    //     this->adjacencies[cPos] = std::vector<Edge>();
    //     centroidShape->setPosition(cPos);
    //     this->objs.push_back(std::move(centroidShape));
    // }-
    float scaleFactor = 1.6f;
    vector<sf::Vector2f> verts = vector<sf::Vector2f>();
    verts.push_back(sf::Vector2f(300*scaleFactor, 5*scaleFactor)); // A0
    verts.push_back(sf::Vector2f(300*scaleFactor, 70*scaleFactor)); // B1
    verts.push_back(sf::Vector2f(230*scaleFactor, 120*scaleFactor)); // C2
    verts.push_back(sf::Vector2f(370*scaleFactor, 120*scaleFactor)); // D3
    verts.push_back(sf::Vector2f(210*scaleFactor, 300*scaleFactor)); // E4
    verts.push_back(sf::Vector2f(250*scaleFactor, 200*scaleFactor)); // F5
    verts.push_back(sf::Vector2f(230*scaleFactor, 320*scaleFactor)); // G6
    verts.push_back(sf::Vector2f(500*scaleFactor, 200*scaleFactor)); // H7
    verts.push_back(sf::Vector2f(359*scaleFactor, 190*scaleFactor)); // I8
    for (auto& v : verts) {
        this->objs.push_back(DPtr(createCircle(v)));
    }
    this->objs.push_back(DPtr(createLine(verts.at(0), verts.at(1))));
    this->objs.push_back(DPtr(createLine(verts.at(1), verts.at(2))));
    this->objs.push_back(DPtr(createLine(verts.at(1), verts.at(3))));
    this->objs.push_back(DPtr(createLine(verts.at(2), verts.at(4))));
    this->objs.push_back(DPtr(createLine(verts.at(3), verts.at(8))));
    this->objs.push_back(DPtr(createLine(verts.at(4), verts.at(5))));
    this->objs.push_back(DPtr(createLine(verts.at(4), verts.at(6))));
    this->objs.push_back(DPtr(createLine(verts.at(6), verts.at(7))));
    this->objs.push_back(DPtr(createLine(verts.at(8), verts.at(7))));

    this->addEdge(verts.at(0), verts.at(1));
    this->addEdge(verts.at(1), verts.at(2));
    this->addEdge(verts.at(1), verts.at(3));
    this->addEdge(verts.at(2), verts.at(4));
    this->addEdge(verts.at(3), verts.at(8));
    this->addEdge(verts.at(4), verts.at(5));
    this->addEdge(verts.at(4), verts.at(6));
    this->addEdge(verts.at(6), verts.at(7));
    this->addEdge(verts.at(7), verts.at(8));
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

std::vector<const sf::Vector2f*> NavMesh::getNeighbours(const sf::Vector2f& n) {
    return vector<const sf::Vector2f*>();
}

const sf::Vector2f* NavMesh::getNearestNode(const sf::Vector2f& n) const {
    auto it = this->adjacencies.lower_bound(n);
    if (it == this->adjacencies.end()) {
        return &(it->first);
    }
    it++;
    return &(it->first);
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