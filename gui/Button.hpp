#pragma once

#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"
#include "luavm/State.hpp"
#include "GuiObject.hpp"
#include <iostream>

// namespace ci {
//     class Button;
//     class ResourceManager;
//     class Gui;
//     class StyleMap;
// }

namespace ci {

class Button : public GuiObject {
public:
    //TODO does this need deleting
    Button(
        std::string id,
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color color,
        GuiObject* parent = 0
    );

    Button(
        mun::Table&,
        mun::State&,
        StyleMap&,
        ResourceManager&
    );

    // Button(const mun::Table& t, ResourceManager& resourceManager);

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

    bool pointInBounds(float x, float y) override;

    void applyStyle(const GuiStyle& style) override;

    void setProperties(const mun::Table& t) override;

private: // MEMBERS
    sf::RectangleShape buttonShape;

};

}