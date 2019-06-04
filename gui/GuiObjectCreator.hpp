#pragma once

#include <memory>
#include "luavm/Table.hpp"
#include "luavm/State.hpp"
#include "GuiObject.hpp"

namespace ci {

class ResourceManager;
class StyleMap;

class GuiObjectCreator {
    friend class GuiObject;
    friend class Gui;
private:
    /**
     * t is the table with the type and the object table as 1 and 2 repsectively
     * s is used so that the object can be bound.
     */
    guiPtr operator()(
        mun::Table& t, 
        mun::State& s, 
        StyleMap& styles, 
        ResourceManager& resourceManager
    ) const;
    // guiPtr makeGuiObject(mun::Table&, mun::State&, StyleMap&, ResourceManager&) const;
    guiPtr makeButton(mun::Table&, mun::State&, StyleMap&, ResourceManager&) const;
    guiPtr makeText(mun::Table&, mun::State&, StyleMap& styles, ResourceManager&) const;
    guiPtr makeTextField(mun::Table&, mun::State&, StyleMap&, ResourceManager&) const;
    guiPtr makePanel(mun::Table&, mun::State&, StyleMap&, ResourceManager&) const;
    void giveDefaultBindings(GuiObject* obj, mun::State& s) const;

};

}