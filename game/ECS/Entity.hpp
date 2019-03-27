#pragma once

#include "SFML/Graphics.hpp"
#include "ComponentAppearance.hpp"
#include "ComponentMovement.hpp"

namespace ci {

class Entity {
public:
    void update(float dt);
    void instantiate(mun::Table& t, ci::ResourceManager& resourceManager);
    void addComponent(const std::string& componentKey, const mun::Table& componentTable);
    void modComponent(const std::string& componentKey, const mun::Table& componentTable);

    bool instanced = false;
};

}