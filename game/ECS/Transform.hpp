#pragma once

#include <cstddef>
#include "luavm/Table.hpp"
#include "PathingDestination.hpp"

namespace ci {

enum class Orientation {W, NW, N, NE, E, SE, S, SW};

// TODO allow conversjon into sf::Vector2f
class Transform {
public:
    Transform();
    Transform(float x, float y, std::size_t areaRef);
    Transform(float x, float y, std::size_t areaRef, Orientation orient);
    Transform(mun::Table& t);
    Transform(mun::Table&& t);
    ~Transform();

    // Transform           getUpdateTransform(const PathingDestination& nextDest, const float timeStep) const;
    // bool                getPositionSatisfied(const PathingDestination& dest) const;
    // operator            Transform();

    std::size_t     areaRef;
    float           x, y;
    Orientation     orient;
};

}