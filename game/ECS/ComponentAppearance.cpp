#include "ComponentAppearance.hpp"
#include "ResourceManager.hpp"

namespace ci {

ComponentAppearance::ComponentAppearance() :
    Component(100)
{}

// TODO should this take responsibility for getting the texture or should the constructor?
ComponentAppearance::ComponentAppearance(mun::Table& t, ci::ResourceManager& resourceManager) :
    Component(t.get<int>("level", 100))
{
    this->sprite.setTexture(*(resourceManager.getResource<sf::Texture>(t.get<const char*>("filename"))));
}

const sf::Sprite& ComponentAppearance::getSprite() const {
    return this->sprite;
}

}