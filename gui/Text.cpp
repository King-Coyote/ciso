#include "Text.hpp"

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
    this->text.setFillColor(color);
    this->text.setPosition(position);
}

void Text::renderDrawables(float dt, sf::RenderTarget& window) {
    window.draw(this->text);
}

void Text::updateDrawables(float dt) {
    
}

void Text::setDrawablesPosition(const sf::Vector2f& position) {
    this->text.setPosition(position);
}

sf::Vector2f Text::getGlobalPos() {
    return this->text.getPosition();
}

sf::Vector2f Text::getLocalPos() {
    return this->localPosition;
}


}