#include <iostream>
#include <cmath>

#include "GuiButton.hpp"

GuiButton::GuiButton(
	std::string id, sf::Vector2f pos, sf::Vector2f size,
	std::string guiStyleId,
	std::string textString,
	EventQueue* mainQ
) {
	this->size = size;
	this->textString = textString;
	this->id = id;
	this->styleId = guiStyleId;
	this->mainQ = mainQ;

	this->setPos(pos);
	this->changeState(GUISTATE_ENABLED);
}

void GuiButton::draw(const float dt, sf::RenderWindow& win) {
	if (this->isHidden) { return; }

	win.draw(this->sprite);
	win.draw(this->text);
}

void GuiButton::update(const float dt) {

}

void GuiButton::setPos(sf::Vector2f pos) {
	this->position = pos;
	this->sprite.setPosition(pos);
	setTextPosition();
}

// TODO maybe move this to the guiObject class
void GuiButton::setStyleId(std::string newId) {
	styleId = newId;
}

bool GuiButton::pointInsideBounds(sf::Vector2i point) {
	return (this->sprite.getGlobalBounds().contains(point.x, point.y));
}

void GuiButton::onMouseEntered() {
	if (this->currentState == GUISTATE_ENABLED) {
		this->changeState(GUISTATE_HOVER);
	}
}

void GuiButton::onMouseExited() {
	if (this->currentState == GUISTATE_HOVER || this->currentState == GUISTATE_CLICKED) {
		this->changeState(GUISTATE_ENABLED);
	}
}

void GuiButton::onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	if (this->currentState == GUISTATE_HOVER) {
		this->changeState(GUISTATE_CLICKED);
	}

}

void GuiButton::onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	if (this->currentState == GUISTATE_CLICKED) {
		this->changeState(GUISTATE_HOVER);
		if (this->mainQ != nullptr) {
			std::shared_ptr<EventGuiButtonClicked> ptr(new EventGuiButtonClicked(this->id, mousePos));
			this->mainQ->postEvent(ptr);
		}
	}

}

void GuiButton::createPolygon() {

	float radius = 3.0f;
	int smooth = 10;
	if (smooth <= 2) { return; }
	float pi = atan(1) * 4;
	float angleInc = (pi/2.0f) / (smooth - 1);

	sf::Vector2f currStartPt = this->position;

	this->sprite = sf::ConvexShape(4*smooth);

	this->sprite.setPointCount(smooth*4);

	// top left corner
	currStartPt.x += radius;
	currStartPt.y += radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = angleInc * i;
		currPt.x -= radius * cos(currAngle);
		currPt.y -= radius * sin(currAngle);
		this->sprite.setPoint(i, currPt);
	}

	// top right corner
	currStartPt.x = (this->position.x + this->size.x) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi/2.0f) - angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y -= radius * sin(currAngle);
		this->sprite.setPoint(i + smooth, currPt);
	}
	
	// bottom right corner
	currStartPt.y = (this->position.y + this->size.y) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		this->sprite.setPoint(i + (smooth*2), currPt);
	}

	// bottom left corner
	currStartPt.x = (this->position.x + radius);
	currStartPt.y = (this->position.y + this->size.y) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi/2.0f) - angleInc * i;
		currPt.x -= radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		this->sprite.setPoint(i + (smooth*3), currPt);
	}

	this->sprite.setOutlineThickness(2);
	this->sprite.setPosition(this->position);

}

void GuiButton::setTextPosition() {
	this->text.getLocalBounds().width;
	sf::Vector2f textSize = sf::Vector2f(
		this->text.getLocalBounds().width,
		this->text.getLocalBounds().height
	);
	this->text.setPosition(
		this->position.x + ((this->size.x - textSize.x) / 2.0f),
		this->position.y + ((this->size.y/2.0f - textSize.y))
	);
}

void GuiButton::initialiseVisualElements() {
	this->createPolygon();
	this->text = sf::Text(this->textString, *(this->guiStyle->getGuaranteedFont()));
	setTextPosition();
}

void GuiButton::changeToStateStyle(GuiState state) {
	if (this->guiStyle == nullptr) {
		return;
	}

	if (this->guiStyle->getBgColor(state) != nullptr) {
		this->sprite.setFillColor(*(this->guiStyle->getBgColor(state)));
	}
	if (this->guiStyle->getOutlineColor(state) != nullptr) {
		this->sprite.setOutlineColor(*(this->guiStyle->getOutlineColor(state)));
	}
	if (this->guiStyle->getStateFont(state) != nullptr) {
		this->text.setFont(*(this->guiStyle->getStateFont(state)));
	}
}