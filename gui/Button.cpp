#include "Button.hpp"

void ci::Button::renderDrawables(float dt, sf::RenderTarget& window) {
    window.draw(this->buttonShape);
    window.draw(this->label);
}

void ci::Button::updateDrawables(float dt) {

}
