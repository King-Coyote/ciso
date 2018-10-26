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

namespace ci {

class ResourceManager;
class EventQueue;
class GuiObjectCreator;
class Button;

class Gui : public EventHandler {
public: // METHODS
    Gui(
        sf::RenderWindow& mainWindow,
        EventQueue& eventQueue,
        ResourceManager& rm
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

private:

    std::vector<guiPtr>     roots;
    sf::RenderWindow*       mainWindow;
    ResourceManager*        resourceManager;
    mun::State              lua;
    StyleMap                styleMap;

    void addToParent(lua_State* L, GuiObject* obj, mun::Ref& parentRef);

    // LUA BOUND FUNCTIONS
    int lua_newButton(lua_State* L);
    int lua_newText(lua_State* L);
    int lua_screenWidth(lua_State* L);
    int lua_screenHeight(lua_State* L);

};

}