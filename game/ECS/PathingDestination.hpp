#pragma once

namespace ci {

class Transform;

class PathingDestination {
public:
    virtual                     ~PathingDestination(){}
    virtual Transform           getUpdateTransform(const PathingDestination& nextDest, const float timeStep) const = 0;
    virtual bool                getPositionSatisfied(const PathingDestination& dest) const = 0;
    virtual operator            Transform() = 0; // this must be transformable into a position
};

}
