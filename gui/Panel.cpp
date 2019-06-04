#include "Panel.hpp"

using namespace std;

namespace ci {

Panel::Panel(
    mun::Table& t,
    mun::State& s,
    StyleMap& styleMap,
    ResourceManager& resourceManager
) :
    GuiObject(t, s, styleMap, resourceManager)
{
    mun::Table size = t.get<mun::Table>("size");
    this->background.setSize(sf::Vector2f(size.get<double>(1), size.get<double>(2)));
    this->setPosition(this->localPosition);
    this->transitionToCurrentState();
}

sf::Vector2f Panel::getGlobalPos() {
    return this->background.getPosition();
}

sf::Vector2f Panel::getLocalPos() {
    return this->localPosition;
}

void Panel::renderDrawables(float dt, sf::RenderTarget& window) {
    window.draw(this->background);
}

void Panel::updateDrawables(float dt) {

}

bool Panel::pointInBounds(float x, float y) {
    return this->background.getGlobalBounds().contains(x, y);
}

void Panel::setDrawablesPosition(const sf::Vector2f& position) {
    this->background.setPosition(position);
}

void Panel::applyStyle(const GuiStyle& style) {
    this->background.setFillColor(style.getBgColor());
    this->background.setOutlineColor(style.getOutlineColor());
    this->background.setOutlineThickness((float)style.getOutlineThickness());
}

}

