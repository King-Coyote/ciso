#include "AppearanceSystem.hpp"

using namespace std;

namespace ci {


void AppearanceSystem::update(
    const float dt, 
    const std::vector<ComponentAppearance>& appearances,
    const std::vector<ComponentTransform>&  transforms
) {

}

void AppearanceSystem::draw(
    const float dt, 
    sf::RenderWindow& window,
    std::vector<ComponentAppearance>& appearances,
    std::vector<ComponentTransform>&  transforms
) {
    for (int i = 0; i<appearances.size(); ++i) {
        if (appearances[i].level < 0) { // < 0 means the compnent does not exist.
            continue;
        }
        appearances[i].setSpritePos(transforms[i].pos);
        window.draw(appearances[i].getSprite());
    }
}

}

