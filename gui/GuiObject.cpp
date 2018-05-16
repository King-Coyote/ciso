#include "GuiObject.hpp"
#include "luavm/Table.hpp"

using namespace std;

namespace ci {

ci::GuiObject::GuiObject() {}

void GuiObject::draw(float dt, sf::RenderTarget& window) {
    this->renderDrawables(dt, window);
    for (auto const& child : this->children) {
        child->draw(dt, window);
    }
}

void GuiObject::update(float dt) {
    this->updateDrawables(dt);
    for (auto const& child : this->children) {
        child->update(dt);
    }
}

void GuiObject::add(unique_ptr<GuiObject> child) {
    this->children.push_back(std::move(child));
}

}