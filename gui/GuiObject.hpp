#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "lua.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "luavm/Function.hpp"
#include "luavm/State.hpp"
#include "Event.hpp"
#include "EventSender.hpp"

namespace ci {

class GuiObject;
class GuiStyle;
class StyleMap;
class EventQueue;
class ResourceManager;

typedef std::shared_ptr<GuiObject> guiPtr;

// if you add another handlerfunctype, also add a global in the Gui subsystem init script
enum HandlerFuncType {
    HANDLERFUNC_CLICK = 0,
    HANDLERFUNC_NOTCLICK,
    NUM_HANDLER_FUNCS // DO NOT DELETE THIS AND LEAVE IT AS LAST ENUM ALWAYS PLS N THANK U
};

enum GuiStateType {
    GUISTATE_DISABLED = 0,
    GUISTATE_ENABLED,
    GUISTATE_HOVER,
    GUISTATE_CLICKED,
    GUISTATE_UNCLICKED, // for like eg if they click but then move mouse outside
    GUISTATE_ACTIVE, // used for things like text entry field to see if they're currently accepting input
    NUM_GUI_STATES // DO NOT DELETE OR ADD ANYTHING AFTER THIS
};

class GuiObject : public EventSender {
public:
    GuiObject(
        std::string id,
        sf::Vector2f position,
        GuiObject* parent = 0
    );
    GuiObject(
        mun::Table& t,
        mun::State& state,
        StyleMap& styleMap,
        ResourceManager& resourceManager
    );
    virtual ~GuiObject() {}

    void draw(float dt, sf::RenderTarget& window);
    void update(float dt);
    void add(guiPtr child);
    void add(GuiObject* child);
    void close();
    bool getIsClosed();
    /**
     * \brief Get this object's root parent (its furthest ancestor)
     * \return the id number for the root parent.
     */
    unsigned getRootNumId();
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
    virtual void handleKeyPressedEvent(EventInput* ei) {}
    virtual void handleKeyReleasedEvent(EventInput* ei) {}
    virtual void handleTextEnteredEvent(EventInput* ei) {}
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
    // int lua_addChildren(lua_State* L);
    int lua_addEventListener(lua_State* L);
    int lua_closeGui(lua_State* L);
    int lua_getId(lua_State* L);
    int lua_setProperties(lua_State* L);
    int lua_pointInsideBounds(lua_State* L);

    mun::Ref userdataRef;
    mun::Ref tableProxy;

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
     * \brief updates the positions of child objects and drawables
     * \param position the parent's global position
     */
    void updatePositions(const sf::Vector2f& position);
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

    /**
     * \brief sets the guiobject's properties eg size, position, functions
     * if the properties are mis-named, they are just ignored
     * \param t the table from lua containing properties
     */
    virtual void setProperties(const mun::Table& t);

    void transitionToCurrentState();
    virtual void applyStyle(const GuiStyle& style) {}

    static unsigned         currentId;
    GuiObject*              parent = nullptr;
    std::vector<guiPtr>     children;
    std::string             id; // used for bookeeping in scripting-verse
    unsigned                numId; // used for internal bookeeping
    sf::Vector2f            localPosition; //<! the position relative to parent. Same as global for roots.
    sf::Vector2f            globalPosition;
    mun::Function           eventFunctors[NUM_HANDLER_FUNCS];
    bool                    isClosed = false;
    bool                    isHidden = false;
    bool                    isDisabled = false;
    std::weak_ptr<GuiStyle> styles[NUM_GUI_STATES];
    GuiStateType            state = GUISTATE_ENABLED;

};

}