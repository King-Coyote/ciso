#include "Panel.hpp"

using namespace std;

namespace ci {

Panel::Panel(
    mun::Table& t,
    StyleMap& styleMap
) :
    GuiObject(t, styleMap)
{
    
}

sf::Vector2f Panel::getGlobalPos() {

}

sf::Vector2f Panel::getLocalPos() {

}

void Panel::renderDrawables(float dt, sf::RenderTarget& window) {

}

void Panel::updateDrawables(float dt) {

}

void Panel::setDrawablesPosition(const sf::Vector2f& position) {

}

void Panel::applyStyle(const GuiStyle& style) {

}

}

