#include "ComponentTransform.hpp"
#include "luavm/Table.hpp"

using namespace std;

namespace ci {

ComponentTransform::ComponentTransform() :
    Component(-1)
{}

ComponentTransform::ComponentTransform(mun::Table& t) :
    Component(0),
    pos(sf::Vector2f(
        t.get<float>("x", 0.0f),
        t.get<float>("y", 0.0f)
    )),
    r(t.get<int>("r", 0))
{}

ComponentTransform::ComponentTransform(mun::Table&& t) :
    Component(0),
    pos(sf::Vector2f(
        t.get<float>("x", 0.0f),
        t.get<float>("y", 0.0f)
    )),
    r(t.get<int>("r", 0))
{}

}

