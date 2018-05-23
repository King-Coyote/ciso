#pragma once

#include <memory>
#include "luavm/Table.hpp"
#include "GuiObject.hpp"

namespace ci {

class ResourceManager;

class GuiObjectCreator {
public:
    GuiObjectCreator(ResourceManager& resourceManager);

    guiPtr makeGuiObject(
        const lvm::Table& t,
        GuiObject* parent = 0
    ) const;

private:
    guiPtr makeButton(
        const lvm::Table& t, 
        GuiObject* parent = 0
    ) const;
    
    guiPtr makeText(
        const lvm::Table& t, 
        GuiObject* parent = 0
    ) const;

    ResourceManager* resourceManager;

};

}