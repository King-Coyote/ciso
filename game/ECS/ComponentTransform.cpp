#include "ComponentTransform.hpp"
#include "luavm/Table.hpp"

using namespace std;

namespace ci {

ComponentTransform::ComponentTransform() :
    Component(-1)
{}

ComponentTransform::ComponentTransform(mun::Table& t) :
    Component(0),
    transform(Transform(
        t.get<float>("x", 0.0f),
        t.get<float>("y", 0.0f),
        (std::size_t)t.get<int>("areaRef", 0)
    ))
{}

ComponentTransform::ComponentTransform(mun::Table&& t) :
    Component(0),
    transform(Transform(
        t.get<float>("x", 0.0f),
        t.get<float>("y", 0.0f),
        (std::size_t)t.get<int>("areaRef", 0)
    ))
{}

ComponentTransform::ComponentTransform(const Transform& rawTransform) :
    Component(0),
    transform(rawTransform)
{}

ComponentTransform& ComponentTransform::operator=(const Transform& rawTransform) {
    this->transform = Transform(rawTransform);
    return *this;
}

}

