#pragma once

#include <string>
#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"
#include "luavm/LuaVM.hpp"
#include "luavm/Ref.hpp"
#include "GuiObject.hpp"
#include "EventHandler.hpp"


class Gui : public EventHandler {
public: // METHODS
    Gui(sf::RenderWindow& mainWindow);

    /**
     * pretty much what you'd expect ay
     * @param dt time step
     */
    void update(float dt);
    /**
     * Call draw on all root gui objects, which will in turn draw their children
     * @param dt time step
     */
    void draw(float dt);

    /**
     * Clear the main gui window for redrawing
     */
    void clear();
    // DELETEME
    void addObj(std::unique_ptr<ci::GuiObject> child) {
        this->roots.push_back(std::move(child));
    }


private: //MEMBERS
    std::vector<std::unique_ptr<ci::GuiObject>> roots;
    sf::RenderWindow* mainWindow;
    lvm::LuaVM vm;

};