#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "ComponentAppearance.hpp"
#include "ComponentTransform.hpp"

namespace ci {

class AppearanceSystem {
public:

    void update(
        const float dt, 
        const std::vector<ComponentAppearance>& appearances,
        const std::vector<ComponentTransform>&  transforms
    );

    void draw(
        const float dt, 
        sf::RenderWindow& window,
        std::vector<ComponentAppearance>& appearances,
        std::vector<ComponentTransform>&  transforms
    );
};

}
