#include "GuiObject.hpp"
#include "luavm/Table.hpp"

using namespace std;

namespace ci {

GuiObject::GuiObject(
    sf::String id,
    sf::Vector2f position,
    GuiObject* parent
) :
    id(id),
    localPosition(position)
{
    if (parent) {
        parent->add(shared_ptr<GuiObject>(this));
    }
}

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

void GuiObject::add(guiPtr child) {
    this->children.push_back(std::move(child));
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
        child->setPosition(position);
    }
}

}