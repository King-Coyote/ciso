#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"
#include "luavm/State.hpp"
#include "GuiObject.hpp"
#include "EventHandler.hpp"

namespace ci {

class StyleMap;
class ResourceManager;

class TextField : public GuiObject {
public:
	TextField(
		mun::Table&,
        mun::State& s,
        StyleMap&,
        ResourceManager&
    );

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
    /**
     * \brief Get position on the window
     * \return the window global position
     */
    sf::Vector2f getGlobalPos() override;
    /**
     * \brief Get the position of the object relative to its parent
     * \return the local (relative to parent) position
     */
    sf::Vector2f getLocalPos() override;

    bool pointInBounds(float x, float y) override;

    void applyStyle(const GuiStyle& style) override;
    void handleMouseReleaseEvent(EventInput* ei) override;
    // void handleMousePressEvent(EventInput* ei) override;
    // void handleMouseMoveEvent(EventInput* ei) override;
    void handleKeyPressedEvent(EventInput* ei) override;
    void handleTextEnteredEvent(EventInput* ei) override;

private:
    sf::RectangleShape  panel;
    sf::RectangleShape  cursorSprite;
    sf::Text            text;
    sf::String          defaultString;
    bool                cursorShown = false;
    sf::Clock           cursorClock;
    unsigned            cursorIndex = 0;

    void updateCursorPosition(unsigned int charIndex);
    unsigned getClickedCharIndex(sf::Vector2i mousePos);
};

}