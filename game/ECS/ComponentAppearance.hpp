#pragma once 

#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"
#include "Component.hpp"
#include "Transform.hpp"

namespace ci {

class ResourceManager;

class ComponentAppearance : public Component {
public:
    ComponentAppearance();
    ComponentAppearance(mun::Table& t, ci::ResourceManager& resourceManager);

    const sf::Sprite& getSprite() const;
private:
    sf::Sprite sprite;
};

}