#pragma once

#include <memory>
#include "luavm/Table.hpp"
#include "GuiObject.hpp"

namespace ci {

class ResourceManager;

class GuiObjectCreator {
public:
    GuiObjectCreator(ResourceManager& resourceManager);

    GuiObject* makeGuiObject(
        const mun::Table& t,
        GuiObject* parent = 0
    ) const;

private:
    GuiObject* makeButton(
        const mun::Table& t, 
        GuiObject* parent = 0
    ) const;
    
    GuiObject* makeText(
        const mun::Table& t, 
        GuiObject* parent = 0
    ) const;

    ResourceManager* resourceManager;

};

}