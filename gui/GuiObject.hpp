#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "lua.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "luavm/Function.hpp"
#include "Event.hpp"

namespace ci {

class GuiObject;
class GuiStyle;
class StyleMap;
class EventQueue;

typedef std::shared_ptr<GuiObject> guiPtr;

enum GuiObjectType {
    NULL_OBJ = 0,
    BUTTON,
    TEXT
};
// if you add another handlerfunctype, also add a global in the Gui subsystem init script
enum HandlerFuncType {
    HANDLERFUNC_CLICK = 0,
    NUM_HANDLER_FUNCS // DO NOT DELETE THIS AND LEAVE IT AS LAST ENUM ALWAYS PLS N THANK U
};

enum GuiStateType {
    GUISTATE_DISABLED = 0,
    GUISTATE_ENABLED,
    GUISTATE_HOVER,
    GUISTATE_CLICKED,
    GUISTATE_UNCLICKED, // for like eg if they click but then move mouse outside
    NUM_GUI_STATES // DO NOT DELETE OR ADD ANYTHING AFTER THIS
};

class GuiObject {
public:
    GuiObject(
        std::string id,
        sf::Vector2f position,
        GuiObject* parent = 0
    );
    GuiObject(
        const mun::Table& t,
        StyleMap& styleMap,
        EventQueue& eventQueue,
        GuiObject* parent = 0
    );
    virtual ~GuiObject() {}

    bool isHidden = false;

    void draw(float dt, sf::RenderTarget& window);
    void update(float dt);
    void add(guiPtr child);
    void add(GuiObject* child);
    void setPosition(const sf::Vector2f& position);
    void close();
    bool getIsClosed();
    /**
     * \name event handlers
     * \brief the functions for handling events passed from the gui subsystem
     * \param event the sfml event ref passed down
     * \return true if the event was handled by this object, false if not.
     */
    ///@{
    virtual void handleMousePressEvent(EventInput* ei);
    virtual void handleMouseReleaseEvent(EventInput* ei);
    virtual void handleMouseMoveEvent(EventInput* ei);
    virtual void handleKeyPressEvent(EventInput* ei);
    virtual void handleKeyReleaseEvent(EventInput* ei);
    ///@}
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

    // LUA FUNCTION BINDINGS
    int lua_addChildren(lua_State* L);
    int lua_addEventListener(lua_State* L);
    int lua_closeGui(lua_State* L);
    int lua_getId(lua_State* L);

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
    /**
     * @brief defines interface for determining whether something is inside bounds of guiobj
     * @param x the x coord of the point
     * @param y the y coord of the point
     * @return true if the point is inside the object
     */
    virtual bool pointInBounds(float x, float y);

    void transitionToCurrentState();
    virtual void applyStyle(const GuiStyle& style) {}

protected:
    EventQueue*             eventQueue;
    GuiObject*              parent;
    std::vector<guiPtr>     children;
    std::string             id;
    sf::Vector2f            localPosition;
    mun::Function           eventFunctors[NUM_HANDLER_FUNCS];
    bool                    isClosed = false;
    std::weak_ptr<GuiStyle> styles[NUM_GUI_STATES];
    GuiStateType            state = GUISTATE_ENABLED;

};

}