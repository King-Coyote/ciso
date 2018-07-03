#include "GuiObject.hpp"
#include "luavm/StackOps.hpp"
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

void GuiObject::add(guiPtr child) {
    this->children.push_back(shared_ptr<GuiObject>(child));
    child->setParent(*this);
    child->setPosition(this->getGlobalPos());
}

void GuiObject::add(GuiObject* child) {
    this->add(shared_ptr<GuiObject>(child));
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

void GuiObject::handleMousePressEvent(const sf::Event& event) {

}

void GuiObject::handleMouseReleaseEvent(const sf::Event& event) {

}

void GuiObject::handleMouseMoveEvent(const sf::Event& event) {

}

void GuiObject::handleKeyPressEvent(const sf::Event& event) {

}

void GuiObject::handleKeyReleaseEvent(const sf::Event& event) {

}

// LUA BINDINGS
int GuiObject::lua_addChildren(lua_State* L) {
    int top = lua_gettop(L);
    mun::printStack(L, "addchildren");
    return 0;
}


}