#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "luavm/Table.hpp"
#include "luavm/State.hpp"
#include "GuiObject.hpp"

namespace ci {

class StyleMap;
class ResourceManager;
class GuiStyle;
class EventQueue;

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

    Text(
        mun::Table&,
        mun::State&,
        StyleMap&,
        ResourceManager&
    );

    sf::Vector2f getGlobalPos() override;
    sf::Vector2f getLocalPos() override;

protected:
        /**
     * \brief Actually draw the widgets to the screen
     * \param time step
     * \param window target to draw to
     */
    void renderDrawables(float dt, sf::RenderTarget& window) override;

    /**
     * \brief Update the drawables inside the widget
     * \param time step
     */
    void updateDrawables(float dt) override;
    /**
     * \brief set the text's global position
     * \param position the global pos to set the text to
     */
    void setDrawablesPosition(const sf::Vector2f& position) override;

    void applyStyle(const GuiStyle& style) override;

    void setProperties(const mun::Table& t) override;

private: // MEMBERS
    sf::Text text;
};

}