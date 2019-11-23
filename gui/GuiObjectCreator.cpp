#include "GuiObjectCreator.hpp"
#include "ResourceManager.hpp"
#include "StyleMap.hpp"
#include "Button.hpp"
#include "TextField.hpp"
#include "Panel.hpp"
#include "Text.hpp"

// Gui object type distinction helper object.
namespace {
enum class GuiObjectType {
    BUTTON,
    TEXT,
    PANEL,
    TEXTFIELD
};
class GuiObjectTypeConv {
public:
    GuiObjectType operator()(const char* str) {
        return GuiObjectTypeConv::convMap.at(std::string(str));
    }
    GuiObjectType operator()(std::string& str) {
        return GuiObjectTypeConv::convMap.at(str);
    }
private:
    static const map<std::string, GuiObjectType> convMap;
};
const map<std::string, GuiObjectType> GuiObjectTypeConv::convMap = {
    {"button", GuiObjectType::BUTTON},
    {"text", GuiObjectType::TEXT},
    {"panel", GuiObjectType::PANEL},
    {"textfield", GuiObjectType::TEXTFIELD}
};

}

namespace ci {

guiPtr GuiObjectCreator::operator()(
    mun::Table& t, 
    mun::State& s, 
    StyleMap& styles,
    ResourceManager& resourceManager
) const {
    auto type = t.get<const char*>("type");
    if (!type) {
        return guiPtr(nullptr);
    }
    switch(GuiObjectTypeConv()(type)) {
    case GuiObjectType::BUTTON:
        return this->makeButton(t, s, styles, resourceManager);
        break;
    case GuiObjectType::PANEL:
        return this->makePanel(t, s, styles, resourceManager);
        break;
    case GuiObjectType::TEXT:
        return this->makeText(t, s, styles, resourceManager);
        break;
    case GuiObjectType::TEXTFIELD:
        return this->makeTextField(t, s, styles, resourceManager);
        break;
    default:
        return guiPtr(nullptr);
    }
}

// GuiObject* GuiObjectCreator::makeGuiObject(mun::Table& t, mun::State& s, StyleMap& styles) const {

// }

guiPtr GuiObjectCreator::makeButton(mun::Table& t, mun::State& s, StyleMap& styles, ResourceManager& resourceManager) const {
    guiPtr obj = make_shared<Button>(t, s, styles, resourceManager);
    this->giveDefaultBindings(obj.get(), s);
    // obj->ref = t;

    return obj;
}

guiPtr GuiObjectCreator::makeText(mun::Table& t, mun::State& s, StyleMap& styles, ResourceManager& resourceManager) const {
    guiPtr obj = make_shared<Text>(t, s, styles, resourceManager);
    this->giveDefaultBindings(obj.get(), s);
    // obj->ref = t;

    return obj;
}

guiPtr GuiObjectCreator::makeTextField(mun::Table& t, mun::State& s, StyleMap& styles, ResourceManager& resourceManager) const {
    guiPtr obj = make_shared<TextField>(t, s, styles, resourceManager);
    this->giveDefaultBindings(obj.get(), s);
    // obj->ref = t;

    return obj;
}

guiPtr GuiObjectCreator::makePanel(mun::Table& t, mun::State& s, StyleMap& styles, ResourceManager& resourceManager) const {
    guiPtr obj = make_shared<Panel>(t, s, styles, resourceManager);
    this->giveDefaultBindings(obj.get(), s);
    // obj->ref = t;

    return obj;
}

void GuiObjectCreator::giveDefaultBindings(GuiObject* obj, mun::State& s) const {
    obj->userdataRef = s.bindClass<GuiObject>("GuiObject", obj)
    .def<&GuiObject::lua_addEventListener>("addEventListener")
    .def<&GuiObject::lua_getId>("getId")
    .def<&GuiObject::lua_closeGui>("close")
    .def<&GuiObject::lua_pointInsideBounds>("pointInsideBounds")
    .def<&GuiObject::lua_setProperties>("setProperties")
    .getRef();
}

// GuiObject* GuiObjectCreator::makeGuiObject(mun:) const {
//     int type = t.get<int>("type");
//     switch((GuiObjectType)type) {
//     case GuiObjectType::BUTTON:
//         return makeButton(t, parent);
//         break;
//     case GuiObjectType::TEXT:
//         return makeText(t, parent);
//         break;
//     default:
//         return nullptr;
//         break;
//     }
// }

// GuiObject* GuiObjectCreator::makeButton(const mun::Table& t, GuiObject* parent) const {
//     // mun::Table size = t.get<mun::Table>("size");
//     // mun::Table position = t.get<mun::Table>("position");
//     // mun::Table color = t.get<mun::Table>("color");

//     // GuiObject* button = new Button(
//     //     t.get<const char*>("id"),
//     //     sf::Vector2f(position.get<double>(1), position.get<double>(2)),
//     //     sf::Vector2f(size.get<double>(1), size.get<double>(2)),
//     //     sf::Color(color.get<int>(1), color.get<int>(2), color.get<int>(3), color.get<int>(4)),
//     //     parent
//     // );

//     // return button;
// }

// GuiObject* GuiObjectCreator::makeText(const mun::Table& t, GuiObject* parent) const {
//     // mun::Table position = t.get<mun::Table>("position");
//     // mun::Table color = t.get<mun::Table>("color");

//     // GuiObject* text = new Text(
//     //     t.get<const char*>("id"),
//     //     sf::Vector2f(position.get<double>(1), position.get<double>(2)),
//     //     sf::String(t.get<const char*>("string")),
//     //     sf::Color(color.get<int>(1), color.get<int>(2), color.get<int>(3), color.get<int>(4)),
//     //     *this->resourceManager->getResource<sf::Font>(t.get<const char*>("font")),
//     //     t.get<int>("fontSize"),
//     //     parent
//     // );

//     // return text;
// }

}