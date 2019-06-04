#include "Button.hpp"
#include "ResourceManager.hpp"
#include "GuiStyle.hpp"
#include "StyleMap.hpp"
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
}

Button::Button(
    mun::Table& t,
    mun::State& s,
    StyleMap& styleMap,
    ResourceManager& resourceManager
) : 
    GuiObject(t, s, styleMap, resourceManager)
{
    mun::Table size = t.get<mun::Table>("size");
    this->buttonShape.setSize(sf::Vector2f(size.get<double>(1), size.get<double>(2)));
    this->transitionToCurrentState();
}


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

void Button::applyStyle(const GuiStyle& style) {
    this->buttonShape.setFillColor(style.getBgColor());
    this->buttonShape.setOutlineColor(style.getOutlineColor());
    this->buttonShape.setOutlineThickness((float)style.getOutlineThickness());
}

sf::Vector2f Button::getGlobalPos() {
    return this->buttonShape.getPosition();
}

sf::Vector2f Button::getLocalPos() {
    return this->localPosition;
}


}