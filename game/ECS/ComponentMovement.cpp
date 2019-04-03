#include "ComponentMovement.hpp"
#include <queue>
#include <limits>
#include <unordered_map>
#include <map>

using namespace std;

namespace ci {

ComponentMovement::ComponentMovement() :
    Component(-1)
{}

ComponentMovement::ComponentMovement(mun::Table& t) : 
    Component(t.get<int>("level", 0))
{

}

ComponentMovement::ComponentMovement(mun::Table&& t) : 
    Component(t.get<int>("level", 0))
{

}

}

