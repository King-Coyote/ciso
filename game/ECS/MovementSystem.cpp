#include <cmath>
#include "MovementSystem.hpp"
//DELETEME
#include <iostream>

using namespace std;

namespace ci {

// x
// FROM a TO b.
inline ci::Transform interpolateTransforms(const Transform& a, const Transform& b, const float dt, float scaling) {
    sf::Vector2f diff = sf::Vector2f(b.x - a.x, b.y - a.y);
    float length = hypot(diff.x, diff.y);
    diff /= length; // normalise
    return ci::Transform(
        a.x + diff.x*dt*100.0f,
        a.y + diff.y*dt*100.0f,
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

MovementSystem::MovementSystem(
    ccontainer<ComponentMovement>&      movementComponents,
    ccontainer<ComponentTransform>&     transformComponents,
    ccontainer<ComponentSpace>&         spaceComponents
) :
    movementComponents(&movementComponents),
    transformComponents(&transformComponents),
    spaceComponents(&spaceComponents),
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
                if (distanceBetween(this->transformComponents->at(path.first).transform, next) < 1) {
                    path.second.pop_back();
                    return false;
                }
                this->transformComponents->at(path.first) = interpolateTransforms(
                    this->transformComponents->at(path.first).transform,
                    next,
                    dt,
                    2.5f + (float)(this->movementComponents->at(path.first).level - 50)*5.0f // TODO this needs to be scaled up and also take into account materials etc
                );
                return false;
            }
        ),
        this->paths.end()
    );
}

void MovementSystem::onCommandMove(EventGameCommandMove* egcm) {
    for (auto ref : egcm->entities) {
        // disallow entities without movement from moving
        if (this->movementComponents->at(ref).level == -1) {
            continue;
        }
        // TODO how to get transforms here? I think you can do it with space but idk yet
        //this->paths.push_back(GET_TRANSFORMS)
        sf::Vector2f src = sf::Vector2f(this->transformComponents->at(ref).transform.x, this->transformComponents->at(ref).transform.y);
        sf::Vector2f dest = sf::Vector2f(egcm->transform.x, egcm->transform.y);
        vector<sf::Vector2f> pathOfVectors = this->spaceComponents->at(egcm->transform.areaRef).navMesh->findPath(src, dest);
        vector<ci::Transform> path = vector<ci::Transform>();
        for (auto& bullshit : pathOfVectors) {
            path.push_back(ci::Transform(bullshit.x, bullshit.y, egcm->transform.areaRef));
        }
        this->paths.push_back(make_pair(ref, path));
    }
}

}

