#include "TraversableNode.hpp"

using namespace std;

namespace ci {

// node_const_iterator NodeQueue::find(const TraversableNode& val) const {
//     auto first = this->c.cbegin();
//     auto last = this->c.cend();
//     while (first!=last) {
//         if (*first==val) return first;
//         ++first;
//     }
//     return last;
// }

const sf::Vector2f TraversableNode::getPos() const {
    return this->worldPos;
}

const std::vector<TraversableNode*>& TraversableNode::getNeighbours() const {
    return this->neighbours;
}

}

