#include "GuiObject.hpp"

std::string GuiObject::getId() {
	return this->id;
}

sf::Vector2f GuiObject::getPos() {
	return this->position;
}

void GuiObject::setPos(sf::Vector2f newPos) {
	this->position = newPos;
}

sf::Vector2f GuiObject::getSize() {
	return this->size;
}

void GuiObject::setSize(sf::Vector2f newSize) {
	this->size = newSize;
}

SwitchResult GuiObject::switchMouseInsideBool(sf::Vector2i mousePos, bool occluded) {

	bool inBoundsAndNotOccluded = (this->pointInsideBounds(mousePos) && !occluded);

	if (!this->mouseInsideSwitch) {
		if (inBoundsAndNotOccluded) {
			this->mouseInsideSwitch = true;
			return SwitchResult::GUISWITCH_ENTERED;
		} else {
			return SwitchResult::GUISWITCH_OUTSIDE;
		}
	} else {
		if (!inBoundsAndNotOccluded) {
			this->mouseInsideSwitch = false;
			return SwitchResult::GUISWITCH_EXITED;
		} else {
			return SwitchResult::GUISWITCH_INSIDE;
		}
	}

}

bool GuiObject::setHidden(bool hidden) {
	bool wasHiddenPreviously = this->isHidden;
	this->isHidden = hidden;
	return wasHiddenPreviously;
}

void GuiObject::setStyle(std::shared_ptr<GuiStyle> style) {
	this->guiStyle = style;
	this->initialiseVisualElements();
	this->changeToStateStyle(this->currentState);
}

std::string GuiObject::getStyleId() {
	return this->styleId;
}

GuiState GuiObject::changeState(GuiState destinationState) {
	GuiState lastState = this->currentState;
	this->currentState = destinationState;
	changeToStateStyle(destinationState);

	return lastState;
}