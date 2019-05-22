#include "ComponentAppearance.hpp"
#include "ResourceManager.hpp"

namespace ci {

ComponentAppearance::ComponentAppearance() :
    Component(-1)
{}

// TODO should this take responsibility for getting the texture or should the constructor?
ComponentAppearance::ComponentAppearance(mun::Table& t, ci::ResourceManager& resourceManager) :
    Component(t.get<int>("level", 100))
{
    this->sprite.setTexture(*(resourceManager.getResource<sf::Texture>(t.get<const char*>("filename"))));
}

ComponentAppearance::ComponentAppearance(mun::Table&& t, ci::ResourceManager& resourceManager) :
    Component(t.get<int>("level", 100))
{
    this->sprite.setTexture(*(resourceManager.getResource<sf::Texture>(t.get<const char*>("filename"))));
}

void ComponentAppearance::setSpritePos(const ci::Transform& transform) {
    this->sprite.setPosition(sf::Vector2f(transform.x, transform.y));
}

const sf::Sprite& ComponentAppearance::getSprite() const {
    return this->sprite;
}

}