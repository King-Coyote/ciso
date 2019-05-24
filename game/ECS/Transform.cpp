#include "Transform.hpp"

using namespace std;

namespace ci {

Transform::Transform() :
    x(0.0f),
    y(0.0f),
    areaRef(0),
    orient(Orientation::W)
{}
Transform::Transform(float x, float y, std::size_t areaRef) :
    x(x),
    y(y),
    areaRef(areaRef),
    orient(Orientation::W)
{}
Transform::Transform(float x, float y, std::size_t areaRef, Orientation orient) :
    x(x),
    y(y),
    areaRef(areaRef),
    orient(orient)
{}
Transform::Transform(mun::Table& t) :
    x(t.get<float>("x", 0.0f)),
    y(t.get<float>("y", 0.0f)),
    areaRef(t.get<int>("areaRef", 0)),
    orient(Orientation::W)
{}
Transform::Transform(mun::Table&& t) :
    x(t.get<float>("x", 0.0f)),
    y(t.get<float>("y", 0.0f)),
    areaRef(t.get<int>("areaRef", 0)),
    orient(Orientation::W)
{}

Transform::~Transform(){}

// Transform Transform::getUpdateTransform(const PathingDestination& nextDest, const float timeStep) const {

//     return ci::Transform(
//         a.x + (b.x - a.x)*dt*scaling,
//         a.y + (b.y - a.y)*dt*scaling,
//         a.areaRef,
//         a.orient
//     );
// }

// bool Transform::getPositionSatisfied(const PathingDestination& dest) const {

// }

// Transform::operator Transform() {
//     return Transform(*this);
// }


}