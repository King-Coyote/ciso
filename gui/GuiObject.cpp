#include "GuiObject.hpp"
#include "luavm/Table.hpp"

using namespace std;

namespace ci {

GuiObject::GuiObject(
    string id,
    sf::Vector2f position,
    GuiObject* parent
) :
    id(id),
    localPosition(position),
    parent(parent)
{}

void GuiObject::draw(float dt, sf::RenderTarget& window) {
    this->renderDrawables(dt, window);
    for (auto const& child : this->children) {
        child->draw(dt, window);
    }
}

void GuiObject::update(float dt) {
    this->updateDrawables(dt);
    for (auto const& child : this->children) {
        child->update(dt);
    }
}

void GuiObject::add(shared_ptr<GuiObject> child) {
    this->children.push_back(shared_ptr<GuiObject>(child));
    child->setParent(*this);
    child->setPosition(this->getGlobalPos());
}

void GuiObject::setParent(GuiObject& parent) {
    this->parent = &parent;
}

void GuiObject::setPosition(const sf::Vector2f& position) {
    if (this->parent) {
        this->setDrawablesPosition(position + this->localPosition);
    } else {
        this->localPosition = position;
        this->setDrawablesPosition(position);
    }
    for (auto const& child : this->children) {
        child->setPosition(this->getGlobalPos());
    }
}

void handleMousePressEvent(const sf::Event& event) {

}

void handleMouseReleaseEvent(const sf::Event& event) {

}

void handleMouseMoveEvent(const sf::Event& event) {

}

void handleKeyPressEvent(const sf::Event& event) {

}

void handleKeyReleaseEvent(const sf::Event& event) {

}


}