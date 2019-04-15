#include "MovementSystem.hpp"
#include <queue>
using namespace std;

namespace ci {

// typedef pair<sf::Vector2f*, float> NodeCost;
template <typename T>
using nodeMap = map<const sf::Vector2f*, T>;

void MovementSystem::update(float dt) {}

inline vector<sf::Vector2f> reconstructPath(map<const sf::Vector2f*, const sf::Vector2f*>& map, const sf::Vector2f* dest) {
    vector<sf::Vector2f> pathPoints;
    // sf::Vector2f* current = dest;
    // while (current != nullptr) {
    //     pathPoints.push_back(current->getPos());
    //     current = map[current];
    // }
    return pathPoints;
} // IMPLEMENT BOAH

inline float getScore(nodeMap<float>& map, const sf::Vector2f* key) {
    if (map.count(key) == 0) {
        return numeric_limits<float>::infinity();
    }
    return map[key];
}

vector<sf::Vector2f> MovementSystem::findPath(
    TraversableGraph<sf::Vector2f>* graph, 
    const sf::Vector2f& src, 
    const sf::Vector2f& dest
) {
    // A* to get a list of points boi
    // the comparison function, which ensures low-cost is at the top of the queue
    // TODO could do this with an unordered_map for costs, like separate g-score from node
    // this would make it more efficient for lookups??

    nodeMap<int>    closed;
    nodeMap<int>    nodeIsOpened;
    nodeMap<float>  gScores;
    nodeMap<float>  fScores;
    auto compare = [&](const sf::Vector2f* a, const sf::Vector2f* b) -> bool {
        return getScore(fScores, a) > getScore(fScores, b);
    };
    priority_queue<const sf::Vector2f*, vector<const sf::Vector2f*>,  decltype(compare)> open(compare);

    const sf::Vector2f* destNode = graph->getNearestNode(dest);
    const sf::Vector2f* start = graph->getNearestNode(src);
    open.push(start);
    map<const sf::Vector2f*, const sf::Vector2f*> cameFrom;
    cameFrom[start] = nullptr;
    const sf::Vector2f* current = nullptr;
    while (!open.empty()) {
        current = open.top();
        if (current == destNode) {
            return reconstructPath(cameFrom, current);
        }
        closed[current] = 1;
        open.pop();
        for (auto& neighbour : graph->getNeighbours(*current)) {
            if (closed.count(neighbour) != 0) {
                continue;
            }
            float gScore = getScore(gScores, current) + graph->getWeightBetween(*current, *neighbour);
            if (nodeIsOpened.count(current) == 0) {
                open.push(neighbour);
                nodeIsOpened[neighbour] = 1;
            } else if (gScore >= gScores[neighbour]){
                continue;
            }
            
            cameFrom[neighbour] = current;
            gScores[neighbour] = gScore;
            // TODO this is just dijkstra's, make a heuristic for final version.
            fScores[neighbour] = gScores[neighbour] + 0.0f;//!!ESTIMATE_HEURISTIC(neighbour, destNode);
        }

    }
    return reconstructPath(cameFrom, current);
    
}
}

