#include <cmath>
#include "MovementSystem.hpp"
//DELETEME
#include <iostream>

using namespace std;

namespace ci {

// FROM a TO b.
inline ci::Transform interpolateTransforms(const Transform& a, const Transform& b, const float dt, float scaling) {
    return ci::Transform(
        a.x + (b.x - a.x)*dt*scaling,
        a.y + (b.y - a.y)*dt*scaling,
        a.areaRef,
        a.orient
    );
}

inline float distanceBetween(const Transform& a, const Transform& b) {
    return hypot(
        a.x - b.x,
        a.y - b.y
    );
}

MovementSystem::MovementSystem() :
    EventHandler({EventType::GAME_COMMAND_MOVE})
    {}

void MovementSystem::update(float dt) {

    this->paths.erase(
        std::remove_if(
            this->paths.begin(),
            this->paths.end(),
            [&](auto& path) -> bool {
                if (path.second.empty()) {
                    return true;
                }
                Transform& next = path.second.back();
                // TODO obviously there needs to be handling of entities going from one area to another
                // like if they get close enough to an object that lets them area transition then that's handled
                // for now, just make it interpolate transforms.
                // TODO make componentTransforms creatable from raw transforms
                if (distanceBetween(this->transformComponents->at(path.first).transform, next) < 0.001) {
                    path.second.pop_back();
                    return false;
                }
                this->transformComponents->at(path.first) = interpolateTransforms(
                    this->transformComponents->at(path.first).transform,
                    next,
                    dt,
                    2.5f + (this->movementComponents->at(path.first).level - 50)*0.05f // TODO this needs to be scaled up and also take into account materials etc
                );
                return false;
            }
        ),
        this->paths.end()
    );
}

void MovementSystem::onCommandMove(EventGameCommandMove* egcm) {
    cout << "MOVING 2: " << egcm->transform.x << ", " << egcm->transform.y << endl;
    for (auto ref : egcm->entities) {
        // disallow entities without movement from moving
        if (this->movementComponents->at(ref).level == -1) {
            continue;
        }
        // TODO how to get transforms here? I think you can do it with space but idk yet
        //this->paths.push_back(GET_TRANSFORMS)
    }
}

}

