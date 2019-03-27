#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "ComponentAppearance.hpp"
#include "ComponentTransform.hpp"

namespace ci {

class AppearanceSystem {
public:
    void update(const float dt);
    void draw(const float dt, sf::RenderWindow& window);
private:
    std::vector<ComponentAppearance>&   appearances;
    std::vector<ComponentTransform>&    transforms;
};

}
