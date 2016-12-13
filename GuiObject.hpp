#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "SFML\Graphics.hpp"

class GuiStyle;

class GuiObject {

protected:
	std::string m_id;
	// position taken from top left of item
	sf::Vector2f m_position;

	// bool for whether the mouse has already entered the object's global bounds
	bool m_mouseInsideSwitch = false;
	bool m_isHidden = false;

	std::unordered_map<std::string, GuiStyle>* m_styleAtlas;

public:

	GuiObject() {}
	~GuiObject() {}

	std::string getId();
	sf::Vector2f getPos();

	// takes a bool from Gui system saying whether mouse was found inside bounds.
	// if true, then it returns 1 if it was previously not inside, -1 if it WAS previously
	// inside and now is not, and 0 otherwise.
	// also switches the mouse inside switch where appropriate.
	int switchMouseInsideBool(bool pointInsideBounds);
	bool setHidden(bool hidden);

	void setStyleAtlas(std::unordered_map<std::string, GuiStyle>* styleAtlas);

	virtual bool pointInsideBounds(sf::Vector2i point) { return false; }

	// Gui-object specific events (NOTE: very much distinct from main events system. Only for use on guiObjects.)
	virtual void onMouseEntered() {}
	virtual void onMouseExited() {}
	virtual void onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {}
	virtual void onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {}

	virtual void draw(const float dt, sf::RenderWindow& win) {}
	virtual void update(const float dt) {}
};