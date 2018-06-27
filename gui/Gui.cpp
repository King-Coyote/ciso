#include "Gui.hpp"
#include "GuiObject.hpp"
#include "GuiObjectCreator.hpp"
#include "Event.hpp"
#include "Button.hpp"

using namespace std;

namespace ci {

Gui::Gui(
    sf::RenderWindow& mainWindow,
    EventQueue& eventQueue,
    ResourceManager& rm
 ) :
    EventHandler(eventQueue, {EventType::CREATE_GUI}),
    mainWindow(&mainWindow)
{
    this->lua.openLibs();
    this->lua.bindGlobalClass("Gui", this)
    .def<&Gui::lua_newButton>("newButton");
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

int Gui::lua_newButton(lua_State* L) {
    mun::Table t(L, 2);

    mun::Table size = t.get<mun::Table>("size");
    mun::Table position = t.get<mun::Table>("position");
    mun::Table color = t.get<mun::Table>("color");

    GuiObject* button = new Button(
        t.get<const char*>("id"),
        sf::Vector2f(position.get<double>(1), position.get<double>(2)),
        sf::Vector2f(size.get<double>(1), size.get<double>(2)),
        sf::Color(color.get<int>(1), color.get<int>(2), color.get<int>(3), color.get<int>(4))
    );

    this->lua.bindClass<GuiObject>("GuiButton", button)
    .def<&GuiObject::clickTest>("onClick")
    .push();

    this->roots.push_back(unique_ptr<GuiObject>(button));

    return 1;
}

}