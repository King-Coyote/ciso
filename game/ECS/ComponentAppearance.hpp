#pragma once 

#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"
#include "Component.hpp"

namespace ci {

class ResourceManager;

class ComponentAppearance : public Component {
public:
    ComponentAppearance();
    ComponentAppearance(mun::Table& t, ci::ResourceManager& resourceManager);
    ComponentAppearance(mun::Table&& t, ci::ResourceManager& resourceManager);

    const sf::Sprite&   getSprite() const;
    void                setSpritePos(sf::Vector2f& pos);
    
private:
    sf::Sprite sprite;
};

}