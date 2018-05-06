#include "GuiObject.hpp"

void ci::GuiObject::draw(float dt, sf::RenderTarget& window) {
    this->renderDrawables(dt, window);
    for (auto const& child : this->children) {
        child->draw(dt, window);
    }
}


void ci::GuiObject::update(float dt) {
    this->updateDrawables(dt);
    for (auto const& child : this->children) {
        child->update(dt);
    }
}


void ci::GuiObject::add(unique_ptr<GuiObject> child) {
    this->children.push_back(std::move(child));
}