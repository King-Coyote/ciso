#include "Button.hpp"
#include "ResourceManager.hpp"
#include <iostream>

using namespace std;

namespace ci {
Button::Button(
    string id,
    sf::Vector2f position,
    sf::Vector2f size,
    sf::Color color,
    GuiObject* parent
) :
GuiObject(id, position, parent),
buttonShape(sf::RectangleShape(size))
{
    buttonShape.setFillColor(color);
    this->setPosition(position);
}

// Button::Button(
//     const mun::Table& t,
//     ResourceManager& resourceManager
// ) :
//     GuiObject(
//         t.get<const char*>("id"),
//         sf::Vector2f(t.get<mun::Table>("position").get<double>(1), t.get<mun::Table>("position").get<double>(2))
//     ),
//     buttonShape(sf::RectangleShape(sf::Vector2f(t.get<mun::Table>("size").get<double>(1), t.get<mun::Table>("size").get<double>(2))))
// {

// }

void Button::renderDrawables(float dt, sf::RenderTarget& window) {
    window.draw(this->buttonShape);
}

void Button::updateDrawables(float dt) {

}

void Button::setDrawablesPosition(const sf::Vector2f& position) {
    this->buttonShape.setPosition(position);
}

bool Button::pointInBounds(float x, float y) {
    return this->buttonShape.getGlobalBounds().contains(x, y);
}

sf::Vector2f Button::getGlobalPos() {
    return this->buttonShape.getPosition();
}

sf::Vector2f Button::getLocalPos() {
    return this->localPosition;
}


}