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
    EventHandler(eventQueue, {EventType::CREATE_GUI}),
    mainWindow(&mainWindow),
    resourceManager(&rm)
{
    this->lua.openLibs();
    this->lua.bindGlobalClass("Gui", this)
    .def<&Gui::lua_newButton>("newButton")
    .def<&Gui::lua_newText>("newText");
}

void Gui::update(float dt) {
    for (auto const& guiObj : this->roots) {
        guiObj->update(dt);
    }
}

void Gui::draw(float dt) {
    for (auto const& guiObj : this->roots) {
        guiObj->draw(dt, *(this->mainWindow));
    }
    this->mainWindow->display();
}

void Gui::clear() {
    this->mainWindow->clear(sf::Color::Black);
}

void Gui::onCreateGui(const std::string& filename) {
    this->lua.runScript(filename);
}

void Gui::addToParent(lua_State* L, GuiObject* obj, mun::Ref& parentRef) {
    GuiObject* parent;
    if (!parentRef) {
        this->roots.push_back(shared_ptr<GuiObject>(obj));
        return;
    }
    parentRef.push();
    GuiObject** parentPtr = (GuiObject**)lua_touserdata(L, -1);
    (*parentPtr)->add(obj);
    lua_pop(L, 1);
}

int Gui::lua_newButton(lua_State* L) {
    mun::Table t(L, 2);

    mun::Table size = t.get<mun::Table>("size");
    mun::Table position = t.get<mun::Table>("position");
    mun::Table color = t.get<mun::Table>("color");
    mun::Ref parentRef = t.get<mun::Ref>("parent");

    GuiObject* button = new Button(
        t.get<const char*>("id"),
        sf::Vector2f(position.get<double>(1), position.get<double>(2)),
        sf::Vector2f(size.get<double>(1), size.get<double>(2)),
        sf::Color(color.get<int>(1), color.get<int>(2), color.get<int>(3), color.get<int>(4))
    );

    this->lua.bindClass<GuiObject>("GuiObject", button)
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
    .push();

    this->addToParent(L, text, parentRef);

    return 1;
}

}