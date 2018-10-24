#include "Text.hpp"
#include "ResourceManager.hpp"
#include "GuiStyle.hpp"
#include "luavm/Table.hpp"

using namespace std;

namespace ci {

Text::Text(
    std::string id,
    sf::Vector2f position,
    sf::String string,
    sf::Color color,
    sf::Font& font,
    unsigned textSize,
    GuiObject* parent
) :
    GuiObject(id, position, parent),
    text(sf::Text(string, font, textSize))
{
    this->setPosition(position);
}

Text::Text(
    const mun::Table& t,
    StyleMap& styleMap,
    ResourceManager& resourceManager
) :
    GuiObject(t, styleMap),
    text(sf::Text(
        sf::String(t.get<const char*>("string", "")),
        *resourceManager.getResource<sf::Font>(t.get<const char*>("font")),
        t.get<int>("fontSize", 12)
    ))
{   
    this->setPosition(this->localPosition);
    this->transitionToCurrentState();
}

void Text::renderDrawables(float dt, sf::RenderTarget& window) {
    window.draw(this->text);
}

void Text::updateDrawables(float dt) {
    
}

void Text::setDrawablesPosition(const sf::Vector2f& position) {
    this->text.setPosition(position);
}

void Text::applyStyle(const GuiStyle& style) {
    this->text.setFillColor(style.getFgColor());
    this->text.setOutlineThickness(style.getOutlineThickness());
    this->text.setOutlineColor(style.getOutlineColor());
}

sf::Vector2f Text::getGlobalPos() {
    return this->text.getPosition();
}

sf::Vector2f Text::getLocalPos() {
    return this->localPosition;
}


}