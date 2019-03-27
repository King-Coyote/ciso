#include "AppearanceSystem.hpp"

using namespace std;

namespace ci {

void AppearanceSystem::update(const float dt) {

}

void AppearanceSystem::draw(const float dt, sf::RenderWindow& window) {
    for (const auto& appearance : this->appearances) {
        if (appearance.level < 0) { // < 0 means the compnent does not exist.
            continue;
        }
        window.draw(appearance.getSprite());
    }
}

}

