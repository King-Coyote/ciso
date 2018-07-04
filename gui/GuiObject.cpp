#include <algorithm>
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
    if (this->isHidden) {
        return;
    }
    this->renderDrawables(dt, window);
    for (auto const& child : this->children) {
        child->draw(dt, window);
    }
}

void GuiObject::update(float dt) {
    this->updateDrawables(dt);
    this->children.erase(
        std::remove_if(
            this->children.begin(),
            this->children.end(),
            [&](guiPtr& child) -> bool {
                child->update(dt);
                return child->getIsClosed();
            }
        ),
        this->children.end()
    );
    // for (auto const& child : this->children) {
    //     child->update(dt);
    // }
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

void GuiObject::close() {
    this->isClosed = true;
    for (auto& child : this->children) {
        child->close();
    }
}

bool GuiObject::getIsClosed() {
    return this->isClosed;
}

bool GuiObject::pointInBounds(float x, float y) {
    return false;
}

bool GuiObject::handleMousePressEvent(const sf::Event& event) {
    bool handled = false;
    for (auto& child : this->children) {
        handled = handled || child->handleMousePressEvent(event);
    }
    if (!handled 
    && this->eventFunctors[HandlerFuncType::CLICK]
    && this->pointInBounds(event.mouseButton.x, event.mouseButton.y)) {
        handled = true;
        this->eventFunctors[HandlerFuncType::CLICK]();
    }
    return handled;
}

bool GuiObject::handleMouseReleaseEvent(const sf::Event& event) {
    return false;
}

bool GuiObject::handleMouseMoveEvent(const sf::Event& event) {
    return false;
}

bool GuiObject::handleKeyPressEvent(const sf::Event& event) {
    return false;
}

bool GuiObject::handleKeyReleaseEvent(const sf::Event& event) {
    return false;
}

// LUA BINDINGS
int GuiObject::lua_addChildren(lua_State* L) {
    int top = lua_gettop(L);
    mun::printStack(L, "addchildren");
    return 0;
}

int GuiObject::lua_addEventListener(lua_State* L) {
    int eventType = lua_tointeger(L, 2);
    if (eventType > -1) {
        this->eventFunctors[eventType] = mun::Function(L, 3);
    }
    return 0;
}

int GuiObject::lua_closeGui(lua_State* L) {
    this->close();
    return 0;
}

int GuiObject::lua_getId(lua_State* L) {
    lua_pushstring(L, this->id.c_str());
    return 1;
}

}