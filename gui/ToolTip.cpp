#include "ToolTip.hpp"

using namespace std;

namespace ci {

ToolTip::ToolTip(
    mun::Table& t,
    mun::State& s,
    StyleMap& styleMap,
    ResourceManager& resourceManager
) :
    GuiObject(t, s, styleMap, resourceManager)
{}

sf::Vector2f ToolTip::getGlobalPos() {

}

sf::Vector2f ToolTip::getLocalPos() {

}

void ToolTip::renderDrawables(float dt, sf::RenderTarget& window) {

}

void ToolTip::updateDrawables(float dt) {

}

void ToolTip::setDrawablesPosition(const sf::Vector2f& position) {

}

void ToolTip::applyStyle(const GuiStyle& style) {

}

}

