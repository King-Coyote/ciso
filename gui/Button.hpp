#pragma once

#include "SFML/Graphics.hpp"
#include "GuiObject.hpp"

namespace ci {
    class Button;
}

class ci::Button {
public:
    Button();
    virtual ~Button();

    void setWidth(const int width);
    void setHeight(const int height);

protected:
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

private: // MEMBERS
    sf::RectangleShape buttonShape;
    sf::Text label;

};