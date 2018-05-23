#pragma once

#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"


namespace ci {

class GuiObject;

typedef std::shared_ptr<GuiObject> guiPtr;

enum GuiObjectType {
    NULL_OBJ = 0,
    BUTTON,
    TEXT
};

class GuiObject {
public:
    GuiObject(
        std::string id,
        sf::Vector2f position,
        GuiObject* parent = 0
    );
    virtual ~GuiObject() {}

    void draw(float dt, sf::RenderTarget& window);
    void update(float dt);
    void add(std::shared_ptr<GuiObject> child);
    void setPosition(const sf::Vector2f& position);

    /**
     * \brief Get position on the window
     * \return the window global position
     */
    virtual sf::Vector2f getGlobalPos() = 0;
    /**
     * \brief Get the position of the object relative to its parent
     * \return the local (relative to parent) position
     */
    virtual sf::Vector2f getLocalPos() = 0;

protected:
    /**
     * \brief Actually draw the widgets to the screen
     * \param dt time step
     * \param window target to draw to
     */
    virtual void renderDrawables(float dt, sf::RenderTarget& window) = 0;
    /**
     * \brief Update the drawables inside the widget
     * \param time step
     */
    virtual void updateDrawables(float dt) = 0;
    /**
     * \brief set the position for the drawables - used by setPosition
     * \param position the new global position for the drawables
     */
    virtual void setDrawablesPosition(const sf::Vector2f& position) = 0;
    /**
     * \brief sets this obj's parent object
     * \param parent the parent reference
     */
    void setParent(GuiObject& parent);

protected:
    GuiObject*          parent;
    std::vector<guiPtr> children;
    std::string         id;
    sf::Vector2f        localPosition;

};

}