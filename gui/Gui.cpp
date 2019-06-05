
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
    .def<&Gui::lua_screenHeight>("screenHeight");

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

int Gui::lua_newObject(lua_State* L) {
    mun::Table t(L, 2);
    guiPtr obj = GuiObjectCreator()(
        t, 
        this->scripting->getState(), 
        this->styleMap, 
        *this->resourceManager
    );
    if (!obj.get()) {
        return 0;
    }
    obj->ref.push();
    this->roots.insert(this->roots.begin(), obj);
    return 1;
}

int Gui::lua_focus(lua_State* L) {
    GuiObject** objFromLua = (GuiObject**)lua_touserdata(L, 2);
    this->focusOnObject(*objFromLua);
}

// guiPtr Gui::createButton(mun::Table& t) {

//     shared_ptr<GuiObject> button = make_shared<Button>(t, this->styleMap);

//     button->ref = this->scripting->getState().bindClass<GuiObject>("GuiObject", button.get())
//     .def<&GuiObject::lua_addEventListener>("addEventListener")
//     .def<&GuiObject::lua_getId>("getId")
//     .def<&GuiObject::lua_closeGui>("close")
//     .push()
//     .getRef();

//     return button;
// }

// guiPtr Gui::createText(mun::Table& t) {

//     shared_ptr<GuiObject> text = make_shared<Text>(Text(t, this->styleMap, *this->resourceManager));

//     text->ref = this->scripting->getState().bindClass<GuiObject>("GuiObject", text.get())
//     .def<&GuiObject::lua_addEventListener>("addEventListener")
//     .def<&GuiObject::lua_getId>("getId")
//     .def<&GuiObject::lua_closeGui>("close")
//     .push()
//     .getRef();

//     return text;
// }

// guiPtr Gui::createTextField(mun::Table& t) {
//     // mun::Ref parentRef = t.get<mun::Ref>("parent");

//     shared_ptr<GuiObject> textField = make_shared<TextField>(TextField(t, this->styleMap, *this->resourceManager));

//     textField->ref = this->scripting->getState().bindClass<GuiObject>("GuiObject", textField.get())
//     .def<&GuiObject::lua_addEventListener>("addEventListener")
//     .def<&GuiObject::lua_getId>("getId")
//     .def<&GuiObject::lua_closeGui>("close")
//     .push()
//     .getRef();

//     // this->addToParent(L, textField, parentRef);

//     return textField;
// }

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

}