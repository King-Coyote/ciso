#pragma once

#include <memory>
#include <vector>

#include "Graphics.hpp"
#include "GuiObject.hpp"
#include "EventHandler.hpp"

using namespace std;

class Gui : public EventHandler {
public: // METHODS
    Gui() {}
    ~Gui() {}

    /**
     * pretty much what you'd expect ay
     * @param time step
     */
    void update(float dt);
    /**
     * Call draw on all root gui objects, which will in turn draw their children
     * @param time step
     * @param window target to draw to
     */
    void draw(float dt, sf::RenderTarget& window);


private: //MEMBERS
    vector<guiPtr> roots;

};