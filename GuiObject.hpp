#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "SFML\Graphics.hpp"

class GuiStyle;

enum SwitchResult {
	GUISWITCH_EXITED, // left the object when it was previously inside
	GUISWITCH_ENTERED, // entered when previously outside
	GUISWITCH_ENTERED_CHILD, //omg lol ;) entered one of the object's children lmao
	GUISWITCH_INSIDE, // it's inside, but was inside last frame too
	GUISWITCH_OUTSIDE // same as above but for outside object
};

// if you need to add more states, ADD AFTER DISABLED AND BEFORE NUM_STATES
// pls
enum GuiState {
	GUISTATE_ENABLED = 0,
	GUISTATE_CLICKED,
	GUISTATE_HOVER,
	GUISTATE_DISABLED,
	GUISTATE_FOCUS,
	GUISTATE_NUM_STATES
};

class GuiObject {

public: // METHODS

	GuiObject(std::string id, sf::Vector2f position, sf::Vector2f size, std::string styleId);
	~GuiObject() {}

	std::string getId();
	sf::Vector2f getPos();
	sf::Vector2f getSize();

	// function that checks if the mouse was inside it and NOT occluded by another this frame.
	// Returns:
	// GUISWITCH_ENTERED if it was OUTSIDE previously but was INSIDE this frame,
	// GUISWITCH_EXITED if it was INSIDE previously but was OUTSIDE this frame,
	// GUISWITCH_INSIDE if it was INSIDE previously and is still INSIDE,
	// GUISWITCH_OUTSIDE if it was OUTSIDE previously and is still OUTSIDE,
	// GUISWITCH_ENTERED_CHILD if it is inside one of the guiObj's child objects.
	virtual SwitchResult switchMouseInsideBool(sf::Vector2i mousePos, bool occluded);
	bool setHidden(bool hidden);

	std::string getStyleId();
	void setStyle(std::shared_ptr<GuiStyle> style);

	virtual void setPos(sf::Vector2f newPos);
	virtual void setSize(sf::Vector2f newSize);

	virtual bool pointInsideBounds(sf::Vector2i point) { return false; }

	// Gui-object specific events (NOTE: very much distinct from main events system. Only for use on guiObjects.)
	// Why use these instead of linking each gui obj to the main event bus?
	// Because the overall gui system often needs to carefully manage who gets what event and in what order.
	// E.g. the onClick events must only be fired once for the first interepting object, not the ones occluded by it.
	virtual void onMouseEntered() {}
	virtual void onMouseExited() {}

	virtual void draw(const float dt, sf::RenderWindow& win) {}
	virtual void update(const float dt) {}

	//================================================================================

protected: // MEMBERS
	std::string id;
	sf::Vector2f position; // position taken from top left of item
	sf::Vector2f size; // x=width, y=height
	std::string styleId;
	std::shared_ptr<GuiStyle> guiStyle;
	GuiState currentState;

	// bool for whether the mouse has already entered the object's global bounds
	bool mouseInsideSwitch = false;
	bool isHidden = false;

protected: // METHODS

	GuiState changeState(GuiState destinationState);

	// VIRTUALS
	// these should be overridden by gui objects.  It should setup sfml drawables etc, and
	// change all their visual elements to match the style associated with the current state.
	virtual void initialiseVisualElements() {}
	virtual void changeToStateStyle(GuiState state) {}

};