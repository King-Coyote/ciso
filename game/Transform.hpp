#pragma once

namespace ci {

enum class Orientation {W, NW, N, NE, E, SE, S, SW};

struct Transform {
    Transform() :
        x(0.0f),
        y(0.0f),
        z(0.0f)
    {}
    Transform(float x, float y, float z) :
        x(x),
        y(y),
        z(z)
    {}

    float       x, y, z;
    Orientation orient;
};

}