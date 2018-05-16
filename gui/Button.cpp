#include "Button.hpp"

using namespace std;

namespace ci {
Button::Button(lvm::Table& t) :
    GuiObject()
{
    lvm::Table size = t.get<lvm::Table>("size");
    lvm::Table position = t.get<lvm::Table>("position");
    lvm::Table color = t.get<lvm::Table>("color");
    this->buttonShape = sf::RectangleShape();
    this->buttonShape.setSize(sf::Vector2f(
        size.get<double>(1),
        size.get<double>(2)
    ));
    this->buttonShape.setPosition(sf::Vector2f(
        position.get<double>(1),
        position.get<double>(2)
    ));
    this->buttonShape.setFillColor(sf::Color(
        color.get<int>(1),
        color.get<int>(2),
        color.get<int>(3),
        color.get<int>(4)
    ));
    this->label = sf::Text();
}

const sf::Vector2f& Button::getSize() {
    return this->buttonShape.getSize();
}

const sf::Vector2f& Button::getPosition() {
    return this->buttonShape.getPosition();
}

const sf::Color& Button::getColor() {
    return this->buttonShape.getFillColor();
}

void Button::setSize(const sf::Vector2f& size) {
    this->buttonShape.setSize(size);
}

void Button::setLabel(const sf::String& label) {
    this->label.setString(label);
}

void Button::setPosition(const sf::Vector2f& position) {
    this->buttonShape.setPosition(position);
    this->label.setPosition(this->buttonShape.getPosition() + sf::Vector2f(10.0f, 10.0f));
}

void Button::renderDrawables(float dt, sf::RenderTarget& window) {
    window.draw(this->buttonShape);
    window.draw(this->label);
}

void Button::updateDrawables(float dt) {

}
}