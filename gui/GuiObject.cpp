#include <algorithm>
#include "GuiObject.hpp"
#include "Gui.hpp"
#include "StyleMap.hpp"
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
{
    this->setPosition(position);
}

GuiObject::GuiObject(
    const mun::Table& t,
    StyleMap& styleMap,
    GuiObject* parent
) :
    id(t.get<const char*>("id", "NULL_ID")),
    parent(parent)
{
    mun::Table position = t.get<mun::Table>("position");
    mun::Table stylesTable = t.get<mun::Table>("style");
    mun::Table defaultStyle = stylesTable.get<mun::Table>("enabled");
    if (defaultStyle) {
        this->styles[GUISTATE_DISABLED] = styleMap.getStyle(stylesTable.get<mun::Table>("enabled", defaultStyle));
        this->styles[GUISTATE_ENABLED] = styleMap.getStyle(defaultStyle);
        this->styles[GUISTATE_HOVER] = styleMap.getStyle(stylesTable.get<mun::Table>("hover", defaultStyle));
        this->styles[GUISTATE_CLICKED] = styleMap.getStyle(stylesTable.get<mun::Table>("clicked", defaultStyle));
        this->styles[GUISTATE_UNCLICKED] = styleMap.getStyle(stylesTable.get<mun::Table>("enabled", defaultStyle));
    }
    this->localPosition = sf::Vector2f(position.get<double>(1), position.get<double>(2));
    if (t.get<bool>("disabled", false)) {
        this->state = GUISTATE_DISABLED;
    } else {
        this->state = GUISTATE_ENABLED;
    }
}

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
    for (auto& child : this->children) {
        child->close();
    }
    this->isClosed = true;
}

bool GuiObject::getIsClosed() {
    return this->isClosed;
}

bool GuiObject::pointInBounds(float x, float y) {
    return false;
}

void GuiObject::transitionToCurrentState() {
    if (auto style = this->styles[this->state].lock()) {
        this->applyStyle(*style.get());
    }
}

void GuiObject::handleMousePressEvent(EventInput* ei) {
    for (auto& child : this->children) {
        child->handleMousePressEvent(ei);
    }
    //GuiStateType prev = this->state;
    if (!ei->isCaptured() && this->pointInBounds(ei->sfEvent.mouseButton.x, ei->sfEvent.mouseButton.y)) {
        ei->capture();
        switch (this->state) {
        case GUISTATE_HOVER:
            this->state = GUISTATE_CLICKED;
            break;
        }
    }
    this->transitionToCurrentState();
}

void GuiObject::handleMouseReleaseEvent(EventInput* ei) {
    for (auto& child : this->children) {
        child->handleMouseReleaseEvent(ei);
    }
    //GuiStateType prev = this->state;
    if (!ei->isCaptured() && this->pointInBounds(ei->sfEvent.mouseButton.x, ei->sfEvent.mouseButton.y)) {
        ei->capture();
        switch (this->state) {
        case GUISTATE_CLICKED:
            this->state = GUISTATE_HOVER;
            if (this->eventFunctors[HANDLERFUNC_CLICK]) {
                this->eventFunctors[HANDLERFUNC_CLICK]();
            }
            break;
        case GUISTATE_UNCLICKED:
            this->state = GUISTATE_ENABLED;
            break;
        }
    }
    this->transitionToCurrentState();
}

void GuiObject::handleMouseMoveEvent(EventInput* ei) {
    for (auto& child : this->children) {
        child->handleMouseMoveEvent(ei);
    }
    //GuiStateType prev = this->state;
    if (!ei->isCaptured() && this->pointInBounds(ei->sfEvent.mouseMove.x, ei->sfEvent.mouseMove.y)) {
        ei->capture();
        switch (this->state) {
        case GUISTATE_ENABLED:
            this->state = GUISTATE_HOVER;
            break;
        case GUISTATE_UNCLICKED:
            this->state = GUISTATE_CLICKED;
            break;
        }
    } else {
        switch (this->state) {
        case GUISTATE_HOVER: 
            this->state = GUISTATE_ENABLED;
            break;
        case GUISTATE_CLICKED:
            this->state = GUISTATE_UNCLICKED;
            break;
        }
    }
    this->transitionToCurrentState();
}

void GuiObject::handleKeyPressEvent(EventInput* ei) {
}

void GuiObject::handleKeyReleaseEvent(EventInput* ei) {
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