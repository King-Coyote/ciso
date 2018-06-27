#include "GuiObjectCreator.hpp"
#include "ResourceManager.hpp"
#include "Button.hpp"
#include "Text.hpp"

using namespace std;

namespace ci {

GuiObjectCreator::GuiObjectCreator(ResourceManager& resourceManager) :
    resourceManager(&resourceManager)
{}

GuiObject* GuiObjectCreator::makeGuiObject(const mun::Table& t, GuiObject* parent) const {
    int type = t.get<int>("type");
    switch((GuiObjectType)type) {
    case GuiObjectType::BUTTON:
        return makeButton(t, parent);
        break;
    case GuiObjectType::TEXT:
        return makeText(t, parent);
        break;
    default:
        return nullptr;
        break;
    }
}

GuiObject* GuiObjectCreator::makeButton(const mun::Table& t, GuiObject* parent) const {
    mun::Table size = t.get<mun::Table>("size");
    mun::Table position = t.get<mun::Table>("position");
    mun::Table color = t.get<mun::Table>("color");

    GuiObject* button = new Button(
        t.get<const char*>("id"),
        sf::Vector2f(position.get<double>(1), position.get<double>(2)),
        sf::Vector2f(size.get<double>(1), size.get<double>(2)),
        sf::Color(color.get<int>(1), color.get<int>(2), color.get<int>(3), color.get<int>(4)),
        parent
    );

    return button;
}

GuiObject* GuiObjectCreator::makeText(const mun::Table& t, GuiObject* parent) const {
    mun::Table position = t.get<mun::Table>("position");
    mun::Table color = t.get<mun::Table>("color");

    GuiObject* text = new Text(
        t.get<const char*>("id"),
        sf::Vector2f(position.get<double>(1), position.get<double>(2)),
        sf::String(t.get<const char*>("string")),
        sf::Color(color.get<int>(1), color.get<int>(2), color.get<int>(3), color.get<int>(4)),
        *this->resourceManager->getResource<sf::Font>(t.get<const char*>("font")),
        t.get<int>("fontSize"),
        parent
    );

    return text;
}

}