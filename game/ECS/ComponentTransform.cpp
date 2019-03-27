#include "ComponentTransform.hpp"
#include "luavm/Table.hpp"

using namespace std;

namespace ci {

ComponentTransform::ComponentTransform(mun::Table& t) :
    x(t.get<float>("x", 0)),
    y(t.get<float>("y", 0)),
    z(t.get<float>("z", 0)),
    r(t.get<int>("r", 0))
{

}

}

