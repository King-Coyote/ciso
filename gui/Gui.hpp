#pragma once

#include <string>
#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"
#include "luavm/State.hpp"
#include "luavm/Table.hpp"
#include "GuiObject.hpp"
#include "EventHandler.hpp"
#include "GuiStyle.hpp"
#include "StyleMap.hpp"
#include "Scripting.hpp"

namespace ci {

class ResourceManager;
class EventQueue;
class GuiObjectCreator;
class Button;

class Gui : public EventHandler {
public: // METHODS
    Gui(
        sf::RenderWindow& mainWindow,
        ResourceManager& rm,
        Scripting& scripting
    );

    /**
     * \brief pretty much what you'd expect ay
     * \param dt time step
     */
    void update(float dt);
    /**
     * \brief Call draw on all root gui objects, which will in turn draw their children
     * \param dt time step
     */
    void draw(float dt);

    /**
     * \brief Clears the main gui window for redrawing
     */
    void clear();

    // EVENT HANDLING
    void onCreateGui(const EventCreateGui* cgep) override;
    void onMousePress(EventInput* ei) override;
    void onMouseRelease(EventInput* ei) override;
    void onMouseMove(EventInput* ei) override;
    void onTextEntered(EventInput* ei) override;
    void onKeyPressed(EventInput* ei) override;
    void onKeyReleased(EventInput* ei) override;

private:

    std::vector<guiPtr>     roots;
    // below holds gui objects that have not been rendered yet by lua using Gui:render().
    // this is to ensure that pointers passed to Lua by Gui:createObject are deleted appropriately if not used.
    std::vector<guiPtr>     pendingRoots;
    sf::RenderWindow*       mainWindow;
    ResourceManager*        resourceManager;
    Scripting*              scripting;
    StyleMap                styleMap;

    void addToParent(lua_State* L, GuiObject* obj, mun::Ref& parentRef);
    void renderLuaObjects();
    int renderLuaObject(const mun::Table& t);
    int renderAsChild(const mun::Table& t);

    void focusOnObject(GuiObject* obj);

    // LUA BOUND FUNCTIONS
    int lua_newObject(lua_State* L);
    int lua_focus(lua_State* L);
    int lua_screenWidth(lua_State* L);
    int lua_screenHeight(lua_State* L);
    int lua_render(lua_State* L);

};

}