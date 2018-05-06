#include "Gui.hpp"
#include "GuiObject.hpp"

void Gui::update(float dt) {
    for (auto const& guiObj : this->roots) {
        guiObj->update(dt);
    }
}

void Gui::draw(float dt, sf::RenderTarget& window) {
    for (auto const& guiObj : this->roots) {
        guiObj->draw(dt, window);
    }
}
