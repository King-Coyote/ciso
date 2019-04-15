#include "Gui.hpp"
#include "GuiObject.hpp"
#include "GuiObjectCreator.hpp"
#include "Event.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "TextField.hpp"
#include "ResourceManager.hpp"

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
    .def<&Gui::lua_newButton>("newButton")
    .def<&Gui::lua_newText>("newText")
    .def<&Gui::lua_newTextField>("newTextField")
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

int Gui::lua_newButton(lua_State* L) {
    mun::Table t(L, 2);
    mun::Ref parentRef = t.get<mun::Ref>("parent");

    GuiObject* button = new Button(t, this->styleMap);

    this->scripting->getState().bindClass<GuiObject>("GuiObject", button)
    .def<&GuiObject::lua_addEventListener>("addEventListener")
    .def<&GuiObject::lua_getId>("getId")
    .def<&GuiObject::lua_closeGui>("close")
    .push();

    this->addToParent(L, button, parentRef);

    return 1;
}

int Gui::lua_newText(lua_State* L) {
    mun::Table t(L, 2);
    mun::Ref parentRef = t.get<mun::Ref>("parent");

    GuiObject* text = new Text(t, this->styleMap, *this->resourceManager);

    this->scripting->getState().bindClass<GuiObject>("GuiObject", text)
    .def<&GuiObject::lua_addEventListener>("addEventListener")
    .def<&GuiObject::lua_getId>("getId")
    .def<&GuiObject::lua_closeGui>("close")
    .push();

    this->addToParent(L, text, parentRef);

    return 1;
}

int Gui::lua_newTextField(lua_State* L) {
    mun::Table t(L, 2);
    mun::Ref parentRef = t.get<mun::Ref>("parent");

    GuiObject* textField = new TextField(t, this->styleMap, *this->resourceManager);

    this->scripting->getState().bindClass<GuiObject>("GuiObject", textField)
    .def<&GuiObject::lua_addEventListener>("addEventListener")
    .def<&GuiObject::lua_getId>("getId")
    .def<&GuiObject::lua_closeGui>("close")
    .push();

    this->addToParent(L, textField, parentRef);

    return 1;
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

}