#include "ComponentMovement.hpp"
#include "TraversableNode.hpp"
#include "TraversableGraph.hpp"
#include <queue>
#include <limits>
#include <unordered_map>
#include <map>

using namespace std;

namespace ci {

// typedef pair<TraversableNode*, float> NodeCost;
template <typename T>
using nodeMap = map<const TraversableNode*, T>;

inline vector<sf::Vector2f> reconstructPath(map<TraversableNode*, TraversableNode*>& map, TraversableNode* dest) {
    vector<sf::Vector2f> pathPoints;
    TraversableNode* current = dest;
    while (current != nullptr) {
        pathPoints.push_back(current->getPos());
        current = map[current];
    }
    return pathPoints;
} // IMPLEMENT BOAH

inline float getScore(nodeMap<float>& map, const TraversableNode* key) {
    if (map.count(key) == 0) {
        return numeric_limits<float>::infinity();
    }
    return map[key];
}

vector<sf::Vector2f> ComponentMovement::findPath(TraversableGraph* graph, const sf::Vector2f& dest) {
    // A* to get a list of points boi
    // the comparison function, which ensures low-cost is at the top of the queue
    // TODO could do this with an unordered_map for costs, like separate g-score from node
    // this would make it more efficient for lookups??

    nodeMap<int>    closed;
    nodeMap<int>    nodeIsOpened;
    nodeMap<float>  gScores;
    nodeMap<float>  fScores;
    auto compare = [&](const TraversableNode* a, const TraversableNode* b) -> bool {
        return getScore(fScores, a) > getScore(fScores, b);
    };
    priority_queue<TraversableNode*, vector<TraversableNode*>,  decltype(compare)> open(compare);

    TraversableNode* destNode = graph->getNearestNode(dest);
    TraversableNode* start = graph->getNearestNode(this->pos);
    open.push(start);
    map<TraversableNode*, TraversableNode*> cameFrom;
    cameFrom[start] = nullptr;
    TraversableNode* current = nullptr;
    while (!open.empty()) {
        current = open.top();
        if (current == destNode) {
            return reconstructPath(cameFrom, current);
        }
        closed[current] = 1;
        open.pop();
        for (auto& neighbour : current->getNeighbours()) {
            if (closed.count(neighbour) != 0) {
                continue;
            }
            float gScore = getScore(gScores, current) + graph->getWeightBetween(current, neighbour);
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

