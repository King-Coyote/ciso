#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "GuiObject.hpp"

//enum GuiAreaState {
//	ENABLED = 0,
//	CLICKED,
//	HOVER,
//	DISABLED,
//	NUM_AREA_STATES
//};

class GuiArea : public GuiObject {

private:

	std::vector<std::shared_ptr<GuiObject>> guiObjs;

public:

	GuiArea(std::string id, sf::Vector2f position, sf::Vector2f size);
	GuiArea(std::string id, sf::Vector2f position, sf::Vector2f size, std::vector<std::shared_ptr<GuiObject>> objs);
	GuiArea(std::string id, sf::Vector2f position, sf::Vector2f size, std::vector<GuiObject*> objs);

	virtual void setPos(sf::Vector2f newPos);

	bool pointInsideBounds(sf::Vector2i point);

	SwitchResult switchMouseInsideBool(sf::Vector2i mousePos, bool occluded);

	void addObj(GuiObject* obj);
	void addObj(std::shared_ptr<GuiObject> obj);

	void onMouseEntered();
	void onMouseExited();

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

};
