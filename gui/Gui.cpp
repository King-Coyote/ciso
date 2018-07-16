#include "Gui.hpp"
#include "GuiObject.hpp"
#include "GuiObjectCreator.hpp"
#include "Event.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "ResourceManager.hpp"

using namespace std;

namespace ci {

Gui::Gui(
    sf::RenderWindow& mainWindow,
    EventQueue& eventQueue,
    ResourceManager& rm
 ) :
    EventHandler(eventQueue, {EventType::CREATE_GUI, EventType::SFML_INPUT}),
    mainWindow(&mainWindow),
    resourceManager(&rm)
{
    this->lua.openLibs();
    this->lua.bindGlobalClass("Gui", this)
    .def<&Gui::lua_newButton>("newButton")
    .def<&Gui::lua_newText>("newText");

    // set up GUI globals
    this->lua.runString(R"(
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

void Gui::onCreateGui(const std::string& filename) {
    this->lua.runScript(filename);
}

void Gui::onMousePress(const sf::Event& e) {
    bool handled = false;
    for (auto& root : this->roots) {
        handled = handled || root->handleMousePressEvent(e);
        if (handled) {
            break;
        }
    }
}

void Gui::onMouseRelease(const sf::Event& e) {
    bool handled = false;
    for (auto& root : this->roots) {
        handled = handled || root->handleMouseReleaseEvent(e);
        if (handled) {
            break;
        }
    }
}

void Gui::onMouseMove(const sf::Event& e) {
    bool handled = false;
    for (auto& root : this->roots) {
        handled = handled || root->handleMouseMoveEvent(e);
        if (handled) {
            break;
        }
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

    this->lua.bindClass<GuiObject>("GuiObject", button)
    .def<&GuiObject::lua_addEventListener>("addEventListener")
    .def<&GuiObject::lua_getId>("getId")
    .def<&GuiObject::lua_closeGui>("close")
    .push();

    this->addToParent(L, button, parentRef);

    return 1;
}

int Gui::lua_newText(lua_State* L) {
    mun::Table t(L, 2);

    mun::Table position = t.get<mun::Table>("position");
    mun::Table color = t.get<mun::Table>("color");
    const char* str = t.get<const char*>("string", "");
    const char* fontName = t.get<const char*>("font", "DejaVuSans.ttf");
    mun::Ref parentRef = t.get<mun::Ref>("parent");

    GuiObject* text = new Text(
        string(t.get<const char*>("id", "NULL_ID")),
        sf::Vector2f(position.get<double>(1), position.get<double>(2)),
        sf::String(str),
        sf::Color(color.get<int>(1), color.get<int>(2), color.get<int>(3), color.get<int>(4)),
        *this->resourceManager->getResource<sf::Font>(fontName),
        t.get<int>("fontSize", 14)
    );

    this->lua.bindClass<GuiObject>("GuiObject", text)
    .def<&GuiObject::lua_addEventListener>("addEventListener")
    .def<&GuiObject::lua_closeGui>("close")
    .def<&GuiObject::lua_getId>("getId")
    .push();

    this->addToParent(L, text, parentRef);

    return 1;
}

}