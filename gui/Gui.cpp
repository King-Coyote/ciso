#include "Gui.hpp"
#include "GuiObject.hpp"

using namespace std;

Gui::Gui(sf::RenderWindow& mainWindow) :
    mainWindow(&mainWindow)
{}

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