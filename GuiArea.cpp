#include "GuiArea.hpp"

// TODO: sort out the GuiStyle behaviour for gui areas
// TODO do you need setPos in these constructors? Other way to do it??

GuiArea::GuiArea(std::string id, sf::Vector2f position, sf::Vector2f size) : 
	GuiObject(id, position, size, "DEFAULT")
{
	this->setPos(position);
}

GuiArea::GuiArea(
	std::string id, sf::Vector2f position, sf::Vector2f size, 
	std::vector<std::shared_ptr<GuiObject>> ptrVector
) :
	GuiObject(id, position, size, "DEFUALT"),
	guiObjs(ptrVector)
{ 
	this->setPos(position);
}

GuiArea::GuiArea(
	std::string id, sf::Vector2f position, sf::Vector2f size, 
	std::vector<GuiObject*> vector
) :
	GuiObject(id, position, size, "DEFAULT")
{
	for (auto obj : vector) {
		std::shared_ptr<GuiObject> ptr(obj);
		this->guiObjs.push_back(ptr);
	}
	this->setPos(position);
}

void GuiArea::setPos(sf::Vector2f pos) {

	this->position = pos;

	for (auto obj : this->guiObjs) {
		obj->setPos(sf::Vector2f(this->position.x + obj->getPos().x, this->position.y + obj->getPos().y));
	}

}

bool GuiArea::pointInsideBounds(sf::Vector2i point) {
	return false;
}

// override of GuiObject one. This needs to look inside at all the objects and essentially do what 
// the gui system does.
SwitchResult GuiArea::switchMouseInsideBool(sf::Vector2i mousePos, bool occluded) {

	bool mouseEnteredFired = false;

	SwitchResult returnVal = SwitchResult::GUISWITCH_OUTSIDE;

	// goes in reverse order so that objects that have just been added are "on top", meaning they
	// get update priority for e.g. mouse entering behaviour.
	for (auto it = this->guiObjs.rbegin(); it != this->guiObjs.rend(); ++it) {
		// this is done prior to update calls so that the GUI system can restrict it to only one
		// gui objet per frame.
		SwitchResult enterSwitch = it->get()->switchMouseInsideBool(mousePos, mouseEnteredFired);
		if (!mouseEnteredFired && 
			(enterSwitch == GUISWITCH_ENTERED || enterSwitch == GUISWITCH_ENTERED_CHILD || enterSwitch == GUISWITCH_INSIDE)) {

			mouseEnteredFired = true;
			if (enterSwitch == GUISWITCH_ENTERED) {
				it->get()->onMouseEntered();
			}
			returnVal = GUISWITCH_ENTERED_CHILD;
		}

		if (enterSwitch == GUISWITCH_EXITED) {
			it->get()->onMouseExited();
		}

	}

	if (!mouseEnteredFired) {
		//// do the normal FSM behaviour for guiobjs.
		returnVal = GuiObject::switchMouseInsideBool(mousePos, occluded);
	}

	return returnVal;

}

void GuiArea::addObj(GuiObject* obj) {
	std::shared_ptr<GuiObject> ptr(obj);
	this->guiObjs.push_back(ptr);
	ptr->setPos(sf::Vector2f(this->position.x + obj->getPos().x, this->position.y + obj->getPos().y));
}

void GuiArea::addObj(std::shared_ptr<GuiObject> obj) {
	this->guiObjs.push_back(obj);
}

void GuiArea::onMouseEntered() {

}

void GuiArea::onMouseExited() {

}

void GuiArea::draw(const float dt, sf::RenderWindow& win) {

	for (auto obj : this->guiObjs) {
		obj->draw(dt, win);
	}

}

void GuiArea::update(const float dt) {

	for (auto obj : this->guiObjs) {
		obj->update(dt);
	}

}