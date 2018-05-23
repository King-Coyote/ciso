#include "Button.hpp"
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

void Button::renderDrawables(float dt, sf::RenderTarget& window) {
    window.draw(this->buttonShape);
}

void Button::updateDrawables(float dt) {

}

void Button::setDrawablesPosition(const sf::Vector2f& position) {
    this->buttonShape.setPosition(position);
}

sf::Vector2f Button::getGlobalPos() {
    return this->buttonShape.getPosition();
}

sf::Vector2f Button::getLocalPos() {
    return this->localPosition;
}


}