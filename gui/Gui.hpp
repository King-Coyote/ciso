#pragma once

#include <string>
#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"
#include "luavm/State.hpp"
#include "luavm/Table.hpp"
#include "GuiObject.hpp"
#include "EventHandler.hpp"

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
    void onCreateGui(const std::string& filename) override;

private:

    std::vector<guiPtr> roots;
    sf::RenderWindow* mainWindow;
    mun::State lua;

    // LUA BOUND FUNCTIONS
    int lua_newButton(lua_State* L);

};

}