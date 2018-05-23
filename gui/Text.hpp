#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GuiObject.hpp"

namespace ci {

class Text : public GuiObject {
public:
    Text(
        std::string id,
        sf::Vector2f position,
        sf::String string,
        sf::Color color,
        sf::Font& font,
        unsigned textSize,
        GuiObject* parent = 0
    );

    sf::Vector2f getGlobalPos();
    sf::Vector2f getLocalPos();

protected:
        /**
     * \brief Actually draw the widgets to the screen
     * \param time step
     * \param window target to draw to
     */
    void renderDrawables(float dt, sf::RenderTarget& window);

    /**
     * \brief Update the drawables inside the widget
     * \param time step
     */
    void updateDrawables(float dt);
    /**
     * \brief set the text's global position
     * \param position the global pos to set the text to
     */
    void setDrawablesPosition(const sf::Vector2f& position);

private: // MEMBERS
    sf::Text text;
};

}