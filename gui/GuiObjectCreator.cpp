#include "GuiObjectCreator.hpp"
#include "ResourceManager.hpp"
#include "Button.hpp"
#include "Text.hpp"

using namespace std;

namespace ci {

GuiObjectCreator::GuiObjectCreator(ResourceManager& resourceManager) :
    resourceManager(&resourceManager)
{}

guiPtr GuiObjectCreator::makeGuiObject(const lvm::Table& t, GuiObject* parent) const {
    int type = t.get<int>("type");
    switch((GuiObjectType)type) {
    case GuiObjectType::BUTTON:
        return makeButton(t, parent);
        break;
    case GuiObjectType::TEXT:
        return makeText(t, parent);
        break;
    default:
        return guiPtr(nullptr);
        break;
    }
}

guiPtr GuiObjectCreator::makeButton(const lvm::Table& t, GuiObject* parent) const {
    lvm::Table size = t.get<lvm::Table>("size");
    lvm::Table position = t.get<lvm::Table>("position");
    lvm::Table color = t.get<lvm::Table>("color");

    shared_ptr<Button> button = shared_ptr<Button>(new Button(
        t.get<const char*>("id"),
        sf::Vector2f(position.get<double>(1), position.get<double>(2)),
        sf::Vector2f(size.get<double>(1), size.get<double>(2)),
        sf::Color(color.get<int>(1), color.get<int>(2), color.get<int>(3), color.get<int>(4)),
        parent
    ));

    lvm::Table children = t.get<lvm::Table>("children");
    for (int i = 1; i <= children.getLength(); i++) { // 1-indexed! Damn you Lua
        this->makeGuiObject(children.get<lvm::Table>(i), button.get());
    }

    return button;
}

guiPtr GuiObjectCreator::makeText(const lvm::Table& t, GuiObject* parent) const {
    lvm::Table position = t.get<lvm::Table>("position");
    lvm::Table color = t.get<lvm::Table>("color");

    guiPtr text = shared_ptr<Text>(new Text(
        t.get<const char*>("id"),
        sf::Vector2f(position.get<double>(1), position.get<double>(2)),
        sf::String(t.get<const char*>("string")),
        sf::Color(color.get<int>(1), color.get<int>(2), color.get<int>(3), color.get<int>(4)),
        *this->resourceManager->getResource<sf::Font>(t.get<const char*>("font")),
        t.get<int>("textSize"),
        parent
    ));

    lvm::Table children = t.get<lvm::Table>("children");
    for (int i = 1; i <= children.getLength(); i++) { // 1-indexed! Damn you Lua
        this->makeGuiObject(children.get<lvm::Table>(i), text.get());
    }

    return text;
}

}