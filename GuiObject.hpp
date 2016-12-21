#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "SFML\Graphics.hpp"

class GuiStyle;

enum SwitchResult {
	EXITED, // left the object when it was previously inside
	ENTERED, // entered when previously outside
	ENTERED_CHILD, //omg lol ;) entered one of the object's children
	NOTHING // nothing of note happened (e.g. inside but was inside last frame too)
};

class GuiObject {

protected:
	std::string m_id;
	// position taken from top left of item
	sf::Vector2f m_position;
	sf::Vector2f m_size;

	// bool for whether the mouse has already entered the object's global bounds
	bool m_mouseInsideSwitch = false;
	bool m_isHidden = false;

	std::unordered_map<std::string, GuiStyle>* m_styleAtlas;

public:

	GuiObject() {}
	~GuiObject() {}

	std::string getId();
	sf::Vector2f getPos();
	sf::Vector2f getSize();

	// takes a bool from Gui system saying whether mouse was found inside bounds.
	// if true, then it returns 1 if it was previously not inside, -1 if it WAS previously
	// inside and now is not, and 0 otherwise. It can also return special value 2, which
	// means that a child of the object was entered.
	// also switches the mouse inside switch where appropriate.
	virtual SwitchResult switchMouseInsideBool(sf::Vector2i mousePos);
	bool setHidden(bool hidden);

	void setStyleAtlas(std::unordered_map<std::string, GuiStyle>* styleAtlas);

	virtual void setPos(sf::Vector2f newPos);
	virtual void setSize(sf::Vector2f newSize);

	virtual bool pointInsideBounds(sf::Vector2i point) { return false; }

	// Gui-object specific events (NOTE: very much distinct from main events system. Only for use on guiObjects.)
	virtual void onMouseEntered() {}
	virtual void onMouseExited() {}
	virtual void onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {}
	virtual void onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {}

	virtual void draw(const float dt, sf::RenderWindow& win) {}
	virtual void update(const float dt) {}
};