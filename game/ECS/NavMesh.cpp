#include <iterator>
#include <cmath>
#include <limits>
#include <iostream>
#include <queue>
#include "NavMesh.hpp"

using namespace std;

namespace ci {

// UTILITY FORWARD DECLARES

sf::CircleShape*    createCircle(sf::Vector2f& pos, float r);
sf::CircleShape*    createCircle(sf::Vector2f& pos, float r, const sf::Color& color);
float               getScore(vector<vector<float>>& map, pair<size_t,size_t>& key);
float               getDistanceBetweenPairs(const Node& a, const Node& b);
float               sign (const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3);
bool                pointInTriangle (const sf::Vector2f& pt, const sf::Vector2f& v1, const sf::Vector2f& v2, const sf::Vector2f& v3);
size_t              getIndex(size_t i, size_t j, size_t sizeX);
bool                compareNodes(const sf::Vector2f& a, const sf::Vector2f& b);

vector<sf::Vector2f> NavMesh::reconstructPath(unordered_map<Node, Node>& map, Node& dest) {
    vector<sf::Vector2f> pathPoints;
    Node current = dest;
    while (map[current] != current) {
        pathPoints.push_back(this->indicesToPosition(current));
        current = map[current];
    }
    return pathPoints;
}

vector<sf::Vector2f> NavMesh::findPath(
    const sf::Vector2f& src, 
    const sf::Vector2f& dest
) {
    // A* to get a list of points boi
    // the comparison function, which ensures low-cost is at the top of the queue

    if (!this->pointInsideMesh(dest)) {
        return vector<sf::Vector2f>();
    }

    vector<vector<bool>> closed = vector<vector<bool>>(this->size.y, vector<bool>(this->size.x, false));
    vector<vector<bool>> nodeIsOpened = vector<vector<bool>>(this->size.y, vector<bool>(this->size.x, false));

    vector<vector<float>> gScores = vector<vector<float>>(this->size.y, vector<float>(this->size.x, numeric_limits<float>::infinity()));
    vector<vector<float>> fScores = vector<vector<float>>(this->size.y, vector<float>(this->size.x, numeric_limits<float>::infinity()));
    auto compare = [&](Node& a, Node& b) -> bool {
        return getScore(fScores, a) > getScore(fScores, b);
    };
    vector<Node> open;

    Node destNode = this->getNearestNode(dest);
    Node start = this->getNearestNode(src);
    //this->objs.push_back(unique_ptr<sf::Drawable>(createCircle(indicesToPosition(start), 3.0f, sf::Color::White)));
    open.push_back(start);
    unordered_map<Node, Node> cameFrom;
    cameFrom[start] = start;
    gScores[start.first][start.second] = 0.0f;
    while (!open.empty()) {
        sort(open.begin(), open.end(), compare);
        pair<size_t,size_t> current = open.back();
        if (current == destNode) {
            return reconstructPath(cameFrom, current);
        }
        closed[current.first][current.second] = true;
        open.pop_back();
        //this->objs.push_back(unique_ptr<sf::Drawable>(createCircle(indicesToPosition(current.first, current.second), 3.0f, sf::Color::Green)));
        for (auto& neighbour : this->getNeighbours(current)) {
            if (closed[neighbour.first][neighbour.second]) {
                continue;
            }
            float gScore = getScore(gScores, current) + this->getWeightBetween(current, neighbour);
            if (!nodeIsOpened[neighbour.first][neighbour.second]) {
                open.push_back(neighbour);
                nodeIsOpened[neighbour.first][neighbour.second] = true;
            } else if (gScore >= getScore(gScores, neighbour)){
                continue;
            }
            
            cameFrom[neighbour] = current;
            gScores[neighbour.first][neighbour.second] = gScore;
            fScores[neighbour.first][neighbour.second] = gScores[neighbour.first][neighbour.second] + getDistanceBetweenPairs(neighbour, destNode)*this->spacing;
        }

    }
    // return reconstructPath(cameFrom, current);
    return vector<sf::Vector2f>();
    
}

NavMesh::NavMesh(std::vector<sf::Vector2f>& pts) :
    EventHandler({EventType::SFML_INPUT})
{
    float minY = numeric_limits<float>::infinity();
    float minX = numeric_limits<float>::infinity();
    float maxY = 0.0f;
    float maxX = 0.0f;
    this->spacing = 10.0f;
    this->position.x = 0;
    this->position.y = 0;
    this->vertices = pts;
    for (auto& pt : this->vertices) {
        pt.x += this->position.x;
        pt.y += this->position.y;
        if (pt.x < minX) minX = pt.x;
        if (pt.y < minY) minY = pt.y;
        if (pt.x > maxX) maxX = pt.x;
        if (pt.y > maxY) maxY = pt.y;
    }
    const size_t rangeX = maxX - minX;
    const size_t rangeY = maxY - minY;
    const size_t pointRange = rangeX * rangeY;
    this->size = sf::Vector2i((int)rangeX, (int)rangeY);
    this->allowedPoints = vector<vector<bool>>(rangeY, vector<bool>(rangeX));
    thor::triangulatePolygon(
        this->vertices.begin(), this->vertices.end(),
        back_inserter(this->triangles)
    );
    for (auto const& tri : this->triangles) {
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
            if (this->pointInsideMesh(pos)) {
                this->allowedPoints[i][j] = true;
                this->objs.push_back(unique_ptr<sf::Drawable>(createCircle(pos, 2.5f)));
            }
        }
    }
}

NavMesh::~NavMesh(){}

bool NavMesh::pointInsideMesh(const sf::Vector2f& pt) const {
    for (auto const& tri : this->triangles) {
        if (pointInTriangle(pt, tri[0], tri[1], tri[2])) {
            return true;
        }
    }
    return false;
}

sf::Vector2f NavMesh::indicesToPosition(const Node& n) const {
    // utility fn to get a position from indices in the navMEsh's allowedpoints collection
    return sf::Vector2f(
        (float)(this->spacing*n.first + this->position.x),
        (float)(this->spacing*n.second + this->position.y)
    );
}

Node NavMesh::positionToIndices(const sf::Vector2f& pos) const {
    return make_pair(
        (size_t)((pos.x - this->position.x)/spacing),
        (size_t)((pos.y - this->position.y)/spacing)
    );
}

void NavMesh::draw(const float dt, sf::RenderWindow& window) {
    for (auto& o : this->objs) {
        window.draw(*o);
    }
}

float NavMesh::getWeightBetween(const Node& a, const Node& b) const {
    return this->spacing;
}

std::vector<Node> NavMesh::getNeighbours(const Node& n) const {
    size_t sizeX = this->allowedPoints[0].size(); // should all be same size
    size_t sizeY = this->allowedPoints.size();
    vector<Node> neighbours;
    for (int j = -1; j<2; ++j) {
        int cardY = n.second + j;
        for (int i = -1; i<2; ++i) {
            int cardX = n.first + i;
            if (cardX >= 0 && cardX < sizeX
            && cardY >= 0 && cardY < sizeY
            && this->allowedPoints[cardX][cardY]
            && !(cardX == n.first && cardY == n.second)) {
                neighbours.push_back(make_pair(cardX, cardY));
            }
        }
    }
    return neighbours;
}

const Node NavMesh::getNearestNode(const sf::Vector2f& n) const {
    pair<size_t,size_t> roundedPair = this->positionToIndices(n);
    if (roundedPair.first > 0 && roundedPair.first < this->size.x
    && roundedPair.second > 0 && roundedPair.second < this->size.y
    && this->allowedPoints[roundedPair.first][roundedPair.second]) {
        return roundedPair;
    }
    float closestDistance = numeric_limits<float>::infinity();
    Node closest = roundedPair;
    for (size_t j=0; j<this->size.y; ++j) {
        for (size_t i = 0; i<this->size.x; ++i) {
            if (!this->allowedPoints[i][j]) {
                continue;
            }
            Node current = make_pair(i,j);
            float distance = getDistanceBetweenPairs(current, roundedPair);
            if (distance < closestDistance) {
                closestDistance = distance;
                closest = current;
            }
        }
    }
    // DELETEME
    cout << "closest node at " << closest.first << "," << closest.second << endl;
    return closest;
}

inline sf::CircleShape* createCircle(sf::Vector2f& pos, float r) {
    sf::CircleShape* c = new sf::CircleShape(r);
    c->setPosition(sf::Vector2f(pos.x - r/2.0f, pos.y - r/2.0f));
    c->setFillColor(sf::Color::Red);
    return c;
}

inline sf::CircleShape* createCircle(sf::Vector2f& pos, float r, const sf::Color& color) {
    sf::CircleShape* c = new sf::CircleShape(r);
    c->setPosition(sf::Vector2f(pos.x - r/2.0f, pos.y - r/2.0f));
    c->setFillColor(color);
    return c;
}

inline float getScore(vector<vector<float>>& map, pair<size_t,size_t>& key) {
    return map[key.first][key.second];
}

inline float getDistanceBetweenPairs(
    const Node& a, 
    const Node& b
) {
    pair<size_t,size_t> diff = make_pair(
        (a.first > b.first? a.first - b.first : b.first - a.first), 
        (a.second > b.second? a.second - b.second : b.second - a.second)
    );
    return hypot(diff.first, diff.second);
}

inline float sign (const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3)
{
    // this basically tells you how p1 lies in relation to the line formed by p2 and p3
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

inline bool pointInTriangle (const sf::Vector2f& pt, const sf::Vector2f& v1, const sf::Vector2f& v2, const sf::Vector2f& v3)
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

inline size_t getIndex(size_t i, size_t j, size_t sizeX) {
    // get the 1d index as if you were using 2d indexing
    return (sizeX * j + i);
}

inline bool compareNodes(const sf::Vector2f& a, const sf::Vector2f& b) {
    // compare lengths of these bois for comparison.
    return (hypot(a.x, a.y) < hypot(b.x, b.y));
}

}