#include <string>
#include "Resource.hpp"

using namespace std;

namespace ci {

template<>
bool Resource<sf::Font>::load(const string& filename) {
    return this->data.loadFromFile("/home/alex/projects/academy/coyoteiso/assets/" + filename);
}

}