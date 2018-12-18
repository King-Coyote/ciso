#include "TraversableGraph.hpp"
#include "TraversableNode.hpp"
#include <limits>
#include <cmath>

using namespace std;

namespace ci {

// // distance between vectors
// inline float getDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
//     sf::Vector2f difference = a - b;
//     return hypot(difference.x, difference.y);
// }

// TraversableNode* TraversableGraph::getNearestNode(const sf::Vector2f& pos) const {

//     TraversableNode* bestNode = nullptr;
//     float shortestDist = numeric_limits<float>::infinity();
//     for (auto const& n : this->nodes) {
//         float distance = getDistance(pos, n->getPos());
//         if (distance < shortestDist) {
//             shortestDist = distance;
//             bestNode = n;
//         }
//     }
//     return bestNode;

// }

// float TraversableGraph::getWeightBetween(TraversableNode* a, TraversableNode* b) const {
//     if (this->adjacencies.count({a, b}) == 0) {
//         return numeric_limits<float>::infinity();
//     }
//     return this->adjacencies.at({a, b});
// }

}

