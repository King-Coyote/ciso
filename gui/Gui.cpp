
#include <algorithm>
#include "Gui.hpp"
#include "GuiObject.hpp"
#include "Event.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "TextField.hpp"
#include "ResourceManager.hpp"
#include "GuiObjectCreator.hpp"

using namespace std;

namespace ci {

Gui::Gui(
    sf::RenderWindow& mainWindow,
    ResourceManager& rm,
    Scripting& scripting
 ) :
    EventHandler({EventType::CREATE_GUI, EventType::SFML_INPUT}),
    mainWindow(&mainWindow),
    resourceManager(&rm),
    scripting(&scripting)
{
    this->scripting->getState().bindGlobalClass("Gui", this)
    .def<&Gui::lua_newObject>("newObject")
    .def<&Gui::lua_focus>("focus")
    .def<&Gui::lua_screenWidth>("screenWidth")
    .def<&Gui::lua_screenHeight>("screenHeight")
    .def<&Gui::lua_render>("render");
    
    // set up GUI globals
    this->scripting->getState().runString(R"(
        GuiEventType = {
            click = 0
        }
    )");
}

void Gui::update(float dt) {
    this->roots.erase(
        std::remove_if(
            this->roots.begin(),
            this->roots.end(),
            [&](guiPtr& child) -> bool {
                child->update(dt);
                return child->getIsClosed();
            }
        ),
        this->roots.end()
    );
    this->pendingRoots.clear();
}

void Gui::draw(float dt) {
    for (auto it = this->roots.rbegin(); it != this->roots.rend(); ++it) {
        (*it).get()->draw(dt, *(this->mainWindow));
    }
    this->mainWindow->display();
}

void Gui::clear() {
    this->mainWindow->clear(sf::Color::Black);
}

void Gui::onCreateGui(const EventCreateGui* cgep) {
    this->scripting->getState().runScript(cgep->filename);
}

void Gui::onMousePress(EventInput* ei) {
    for (auto& root : this->roots) {
        if (ei->isCaptured()) {
            break;
        }
        root->handleMousePressEvent(ei);
    }
}

void Gui::onMouseRelease(EventInput* ei) {
    for (auto& root : this->roots) {
        if (ei->isCaptured()) {
            break;
        }
        root->handleMouseReleaseEvent(ei);
    }
}

void Gui::onMouseMove(EventInput* ei) {
    for (auto& root : this->roots) {
        if (ei->isCaptured()) {
            break;
        }
        root->handleMouseMoveEvent(ei);
    }
}

void Gui::onTextEntered(EventInput* ei) {
    for (auto& root : this->roots) {
        if (ei->isCaptured()) {
            break;
        }
        root->handleTextEnteredEvent(ei);
    }
}

void Gui::onKeyPressed(EventInput* ei) {
    for (auto& root : this->roots) {
        if (ei->isCaptured()) {
            break;
        }
        root->handleKeyPressedEvent(ei);
    }
}

void Gui::onKeyReleased(EventInput* ei) {
    for (auto& root : this->roots) {
        if (ei->isCaptured()) {
            break;
        }
        root->handleKeyReleasedEvent(ei);
    }
}

void Gui::addToParent(lua_State* L, GuiObject* obj, mun::Ref& parentRef) {
    GuiObject* parent;
    if (!parentRef) {
        this->roots.insert(this->roots.begin(), shared_ptr<GuiObject>(obj));
        return;
    }
    parentRef.push();
    GuiObject** parentPtr = (GuiObject**)lua_touserdata(L, -1);
    (*parentPtr)->add(obj);
    lua_pop(L, 1);
}

void Gui::focusOnObject(GuiObject* objToFocus) {
    guiPtr obj;
    this->roots.erase(std::remove_if(
        this->roots.begin(),
        this->roots.end(),
        [&](guiPtr& root) {
            if (objToFocus == root.get()) {
                obj = std::move(root);
                return true;
            }
            return false;
        }
    ));
    this->roots.insert(this->roots.begin(), obj);
}

// DELETEME probably
int Gui::lua_newObject(lua_State* L) {
    // mun::Table t(L, 2);
    // guiPtr obj = GuiObjectCreator()(
    //     t, 
    //     this->scripting->getState(), 
    //     this->styleMap, 
    //     *this->resourceManager
    // );
    // if (!obj.get()) {
    //     return 0;
    // }
    // lua_setmetatable(L, 2);
    // return 1;
    return 0;
}

int Gui::lua_focus(lua_State* L) {
    GuiObject** objFromLua = (GuiObject**)lua_touserdata(L, 2);
    this->focusOnObject(*objFromLua);
    return 0;
}

int Gui::lua_screenWidth(lua_State* L) {
    unsigned width = this->mainWindow->getSize().x;
    lua_pushinteger(L, width);
    return 1;
}

int Gui::lua_screenHeight(lua_State* L) {
    unsigned height = this->mainWindow->getSize().y;
    lua_pushinteger(L, height);
    return 1;
}

int Gui::lua_render(lua_State* L) {
    mun::Table items(L, -1);
    for (int i : items.indices()) {
        mun::Table current = items.get<mun::Table>(i);
        current.push();
        guiPtr obj = GuiObjectCreator()(
            current, 
            this->scripting->getState(), 
            this->styleMap, 
            *this->resourceManager
        );
        if (!obj.get()) {
            return 0;
        }
        this->roots.insert(this->roots.begin(), obj);
        obj->ref.push();
        lua_setfield(L, -2, "call");
        lua_pop(L, 1);
    }
    return 0;
}

int Gui::renderLuaObject(const mun::Table& t) {
    
}

int Gui::renderAsChild(const mun::Table& t) {

}

}