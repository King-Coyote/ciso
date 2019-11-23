#include <algorithm>
#include "GuiObject.hpp"
#include "GuiObjectCreator.hpp"
#include "ResourceManager.hpp"
#include "Gui.hpp"
#include "StyleMap.hpp"
#include "EventQueue.hpp"
#include "luavm/StackOps.hpp"
#include "luavm/Table.hpp"
//DELETEME
#include <iostream>

using namespace std;

namespace ci {

unsigned GuiObject::currentId = 0;

GuiObject::GuiObject(
    string id,
    sf::Vector2f position,
    GuiObject* parent
) :
    id(id),
    numId(GuiObject::currentId++),
    localPosition(position),
    parent(parent)
{
}

GuiObject::GuiObject(
    mun::Table& t,
    mun::State& state,
    StyleMap& styleMap,
    ResourceManager& resourceManager
) :
    id(t.get<const char*>("id", "NULL_ID")),
    numId(GuiObject::currentId++)
{
    mun::Table stylesTable = t.get<mun::Table>("style");
    mun::Table defaultStyle = stylesTable.get<mun::Table>("enabled");
    if (defaultStyle) {
        this->styles[GUISTATE_ENABLED] = styleMap.getStyle(defaultStyle);
        this->styles[GUISTATE_DISABLED] = styleMap.getStyle(stylesTable.get<mun::Table>("enabled", defaultStyle));
        this->styles[GUISTATE_HOVER] = styleMap.getStyle(stylesTable.get<mun::Table>("hover", defaultStyle));
        this->styles[GUISTATE_CLICKED] = styleMap.getStyle(stylesTable.get<mun::Table>("clicked", defaultStyle));
        this->styles[GUISTATE_UNCLICKED] = styleMap.getStyle(stylesTable.get<mun::Table>("enabled", defaultStyle));
        this->styles[GUISTATE_ACTIVE] = styleMap.getStyle(stylesTable.get<mun::Table>("active", defaultStyle));
    }

    // mun::Table childrenTable = t.get<mun::Table>("children");
    // if (childrenTable) {
    //     for (auto& key : childrenTable.indices()) {
    //         mun::Table childObjTable = childrenTable.get<mun::Table>(key);
    //         this->add(GuiObjectCreator()(childObjTable, state, styleMap, resourceManager));
    //     }
    // }

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
}

void GuiObject::add(GuiObject* child) {
    this->add(shared_ptr<GuiObject>(child));
}

void GuiObject::setParent(GuiObject& parent) {
    this->parent = &parent;
}

void GuiObject::updatePositions(const sf::Vector2f& position) {
    if (!this->parent) {
        // root obj, global = local
        this->globalPosition = position;
    } else {
        // child obj, global =/= local
        this->globalPosition = position + this->localPosition;
    }
    this->setDrawablesPosition(this->globalPosition);
    for (auto const& child : this->children) {
        child->updatePositions(this->globalPosition);
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

unsigned GuiObject::getRootNumId() {
    if (!this->parent) {
        return this->numId;
    }
    return this->parent->getRootNumId();
}

bool GuiObject::pointInBounds(float x, float y) {
    return false;
}

void GuiObject::setProperties(const mun::Table& t) {
    mun::Table positionTable = t.get<mun::Table>("position");
    if (positionTable) {
        sf::Vector2f position = sf::Vector2f(
            positionTable.get<float>(1),
            positionTable.get<float>(2)
        );
        this->localPosition = position;
        this->updatePositions(position);
    }
    this->isHidden = t.get<bool>("hidden", this->isHidden);
    this->isDisabled = t.get<bool>("disabled", this->isDisabled);
    if (this->isDisabled) {
        this->state = GUISTATE_DISABLED;
    } else {
        this->state = GUISTATE_ENABLED;
    }

    // LUA-SIDE EVENT HANDLERS
    if (t.contains("handleOnClick"))
        this->eventFunctors[HANDLERFUNC_CLICK] = t.get<mun::Function>("handleOnClick");
    if (t.contains("handleOnNotClick"))
        this->eventFunctors[HANDLERFUNC_NOTCLICK] = t.get<mun::Function>("handleOnNotClick");
}

void GuiObject::transitionToCurrentState() {
    if (auto style = this->styles[this->state].lock()) {
        this->applyStyle(*style.get());
    }
}

void GuiObject::handleMousePressEvent(EventInput* ei) {
    if (this->isHidden) {
        return;
    }
    for (auto& child : this->children) {
        child->handleMousePressEvent(ei);
    }
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
    if (this->isHidden) {
        return;
    }
    for (auto& child : this->children) {
        child->handleMouseReleaseEvent(ei);
    }
    if (!ei->isCaptured()) {
        if (this->pointInBounds(ei->sfEvent.mouseButton.x, ei->sfEvent.mouseButton.y)) {
            ei->capture();
            switch (this->state) {
            case GUISTATE_CLICKED:
                this->state = GUISTATE_HOVER;
                // notify all listeners that this button hath been cliqq'd
                this->postEvent(new EventGuiButtonClicked(this->id));
                if (this->eventFunctors[HANDLERFUNC_CLICK]) {
                    this->eventFunctors[HANDLERFUNC_CLICK](
                        this->tableProxy, 
                        ei->sfEvent.mouseButton.x,
                        ei->sfEvent.mouseButton.y,
                        (ei->sfEvent.mouseButton.button == sf::Mouse::Left?0:1)
                    );
                }
                break;
            case GUISTATE_UNCLICKED:
                this->state = GUISTATE_ENABLED;
                break;
            }
        } else {
            if (this->eventFunctors[HANDLERFUNC_NOTCLICK]) {
                this->eventFunctors[HANDLERFUNC_NOTCLICK](
                    this->tableProxy, 
                    ei->sfEvent.mouseButton.x,
                    ei->sfEvent.mouseButton.y,
                    (ei->sfEvent.mouseButton.button == sf::Mouse::Left?0:1)
                );
            }
        }
    }
    this->transitionToCurrentState();
}

void GuiObject::handleMouseMoveEvent(EventInput* ei) {
    if (this->isHidden) {
        return;
    }
    for (auto& child : this->children) {
        child->handleMouseMoveEvent(ei);
    }
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

int GuiObject::lua_setProperties(lua_State* L) {
    mun::Table t(L, 2);
    this->setProperties(t);
    return 0;
}

int GuiObject::lua_pointInsideBounds(lua_State* L) {
    int x = lua_tointeger(L, 2);
    int y = lua_tointeger(L, 3);
    lua_pushboolean(L, this->pointInBounds(x, y));
    return 1;
}

} 