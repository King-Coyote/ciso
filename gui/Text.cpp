#include "Text.hpp"
#include "ResourceManager.hpp"
#include "GuiStyle.hpp"
#include "EventQueue.hpp"

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
}

Text::Text(
    mun::Table& t,
    mun::State& s,
    StyleMap& styleMap,
    ResourceManager& resourceManager
) :
    GuiObject(t, s, styleMap, resourceManager)
{   
    this->text.setFont(*resourceManager.getResource<sf::Font>(t.get<const char*>("font", "default")));
    this->setProperties(t);
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

void Text::setProperties(mun::Table& t) {
    this->GuiObject::setProperties(t);
    if (t.contains("string")) {this->text.setString(sf::String(t.get<const char*>("string")));}
    if (t.contains("fontSize")) {this->text.setCharacterSize(t.get<int>("fontSize"));}
}


}