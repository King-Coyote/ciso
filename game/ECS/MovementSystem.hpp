#pragma once

#include <vector>
#include "SFML/System.hpp"
#include "EventHandler.hpp"
#include "Transform.hpp"
#include "ComponentMovement.hpp"
#include "ComponentTransform.hpp"
#include "ComponentSpace.hpp"

template <typename T>
using ccontainer = std::vector<T>;

typedef std::pair<std::size_t, std::vector<ci::Transform>> entityPath;

namespace ci {

class MovementSystem : public EventHandler {
public:
    MovementSystem();
    MovementSystem(
        ccontainer<ComponentMovement>&      movementComponents,
        ccontainer<ComponentTransform>&     transformComponents,
        ccontainer<ComponentSpace>&         spaceComponents
    );
    void update(float dt);
    
    // Event handlers
    void onCommandMove(EventGameCommandMove* egcm) override;
private:
    std::vector<entityPath> paths;
    ccontainer<ComponentMovement>*      movementComponents;
    ccontainer<ComponentTransform>*     transformComponents;
    ccontainer<ComponentSpace>*         spaceComponents;

};

}