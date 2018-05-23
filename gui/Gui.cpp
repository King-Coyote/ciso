#include "Gui.hpp"
#include "GuiObject.hpp"
#include "GuiObjectCreator.hpp"
#include "Event.hpp"

using namespace std;

namespace ci {

Gui::Gui(
    sf::RenderWindow& mainWindow,
    EventQueue& eventQueue,
    ResourceManager& rm
 ) :
    EventHandler(eventQueue, {EventType::CREATE_GUI}),
    mainWindow(&mainWindow),
    creator(unique_ptr<GuiObjectCreator>(new GuiObjectCreator(rm)))
{
    this->vm.openLibs();
    this->initLuaGuiObjects();
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
    lvm::Table obj = this->vm.refFromFile<lvm::Table>(filename);
    this->roots.push_back(move(creator->makeGuiObject(obj)));
}

void Gui::initLuaGuiObjects() {
    this->vm.runString(R"(
        GuiObject = {
            id = "",
            type = 0,
            position = {0, 0},
            children = {}
        }
        function GuiObject:new(o)
            o = o or {}
            setmetatable(o, self)
            self.__index = self
            return o
        end

        Button = GuiObject:new{
            type = 1,
            size = {50, 50},
            color = {170, 170, 170, 255}
        }

        Text = GuiObject:new{
            type = 2,
            string = "",
            font = "DejaVuSans.ttf",
            fontSize = 12,
            color = {0, 0, 0, 255}
        }
        )"
    );
}

}