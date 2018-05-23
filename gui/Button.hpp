#pragma once

#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"
#include "GuiObject.hpp"

namespace ci {
    class Button;
}

class ci::Button : public ci::GuiObject {
public:
    Button(
        sf::String id,
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color color,
        GuiObject* parent = 0
    );

    sf::Vector2f getGlobalPos();
    sf::Vector2f getLocalPos();

protected:
        /**
     * \brief Actually draw the widgets to the screen
     * \param dt time step
     * \param window target to draw to
     */
    void renderDrawables(float dt, sf::RenderTarget& window) override;

    /**
     * \brief Update the drawables inside the widget
     * \param dt time step
     */
    void updateDrawables(float dt) override;
    /**
     * \brief update the RectangleShape's position
     * \param position the global position to set the rectangleshape to
     */
    void setDrawablesPosition(const sf::Vector2f& position) override;

private: // MEMBERS
    sf::RectangleShape buttonShape;

};