#pragma once

#include <cstddef>
#include "luavm/Table.hpp"

namespace ci {

enum class Orientation {W, NW, N, NE, E, SE, S, SW};

// TODO allow conversjon into sf::Vector2f
struct Transform {
    Transform() :
        x(0.0f),
        y(0.0f),
        areaRef(0),
        orient(Orientation::W)
    {}
    Transform(float x, float y, std::size_t areaRef) :
        x(x),
        y(y),
        areaRef(areaRef),
        orient(Orientation::W)
    {}
    Transform(float x, float y, std::size_t areaRef, Orientation orient) :
        x(x),
        y(y),
        areaRef(areaRef),
        orient(orient)
    {}
    Transform(mun::Table& t) :
        x(t.get<float>("x", 0.0f)),
        y(t.get<float>("y", 0.0f)),
        areaRef(t.get<int>("areaRef", 0)),
        orient(Orientation::W)
    {}
    Transform(mun::Table&& t) :
        x(t.get<float>("x", 0.0f)),
        y(t.get<float>("y", 0.0f)),
        areaRef(t.get<int>("areaRef", 0)),
        orient(Orientation::W)
    {}

    std::size_t     areaRef;
    float           x, y;
    Orientation     orient;
};

}