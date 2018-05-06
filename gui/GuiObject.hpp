#pragma once

#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"
#include "Gui.hpp"

using namespace std;

namespace ci {
    class GuiObject;
}

typedef unique_ptr<ci::GuiObject> guiPtr;

class ci::GuiObject {
public:
    GuiObject();
    virtual ~GuiObject() {}

    void draw(float dt, sf::RenderTarget& window);
    void update(float dt);
    void add(unique_ptr<GuiObject> child);

protected:// METHODS
    /**
     * Actually draw the widgets to the screen
     * @param time step
     * @param window target to draw to
     */
    virtual void renderDrawables(float dt, sf::RenderTarget& window) = 0;

    /**
     * Update the drawables inside the widget
     * @param time step
     */
    virtual void updateDrawables(float dt) = 0;

protected: // MEMBERS
    vector<guiPtr> children;

};