#pragma once

#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"
#include "GuiObject.hpp"

namespace ci {
    class Button;
}

class ci::Button : public ci::GuiObject {
public:
    Button(lvm::Table& t);

    void setSize(const sf::Vector2f& size);
    void setLabel(const sf::String& label);
    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getSize();
    const sf::Vector2f& getPosition();
    const sf::Color& getColor();

protected:
        /**
     * Actually draw the widgets to the screen
     * @param time step
     * @param window target to draw to
     */
    void renderDrawables(float dt, sf::RenderTarget& window);

    /**
     * Update the drawables inside the widget
     * @param time step
     */
    void updateDrawables(float dt);

private: // MEMBERS
    sf::RectangleShape buttonShape;
    sf::Text label;

};