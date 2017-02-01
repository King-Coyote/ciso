#include <iostream>
#include <cmath>

#include "GuiButton.hpp"
#include "SFML\Graphics.hpp"
#include "GuiStyle.hpp"

GuiButton::GuiButton() {
	m_id = "";
	this->setPos(sf::Vector2f(150.0f,150.0f));
	this->changeState(GUISTATE_ENABLED);
}

GuiButton::GuiButton(
	std::string id, sf::Vector2f pos, sf::Vector2f size,
	std::string guiStyleId,
	std::string text,
	EventQueue* mainQ
) {
	m_size = size;
	m_id = id;
	this->styleId = guiStyleId;
	this->createPolygon();
	this->setPos(pos);

	m_mainQ = mainQ;

	this->changeState(GUISTATE_ENABLED);

}

GuiState GuiButton::changeState(GuiState destinationState) {

	GuiState lastState = m_currentState;
	m_currentState = destinationState;

	changeToStateStyle(destinationState);

	return lastState;
	
}

void GuiButton::changeToStateStyle(GuiState destinationState) {
	if (this->m_guiStyle == nullptr) { 
		return; 
	}

	if (m_guiStyle->getBgColor(destinationState) != nullptr) {
		this->sprite.setFillColor(*(m_guiStyle->getBgColor(destinationState)));
	}
	if (m_guiStyle->getOutlineColor(destinationState) != nullptr) {
		this->sprite.setOutlineColor(*(m_guiStyle->getOutlineColor(destinationState)));
	}
}

void GuiButton::draw(const float dt, sf::RenderWindow& win) {
	win.draw(this->sprite);
	win.draw(m_text);
}

void GuiButton::update(const float dt) {

	

}

void GuiButton::setPos(sf::Vector2f pos) {
	m_position = pos;
	this->sprite.setPosition(pos);
	m_text.setPosition(pos);
}

// TODO maybe move this to the guiObject class
void GuiButton::setStyleId(std::string newId) {
	styleId = newId;
}

bool GuiButton::pointInsideBounds(sf::Vector2i point) {
	return (this->sprite.getGlobalBounds().contains(point.x, point.y));
}

void GuiButton::onMouseEntered() {
	if (m_currentState == GUISTATE_ENABLED) {
		this->changeState(GUISTATE_HOVER);
	}
}

void GuiButton::onMouseExited() {
	if (m_currentState == GUISTATE_HOVER || m_currentState == GUISTATE_CLICKED) {
		this->changeState(GUISTATE_ENABLED);
	}
}

void GuiButton::onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	if (m_currentState == GUISTATE_HOVER) {
		this->changeState(GUISTATE_CLICKED);
	}

}

void GuiButton::onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	if (m_currentState == GUISTATE_CLICKED) {
		this->changeState(GUISTATE_HOVER);
		if (m_mainQ != nullptr) {
			std::shared_ptr<EventGuiButtonClicked> ptr(new EventGuiButtonClicked(m_id, mousePos));
			m_mainQ->postEvent(ptr);
		}
	}

}

void GuiButton::createPolygon() {

	float radius = 3.0f;
	int smooth = 10;
	if (smooth <= 2) { return; }
	float pi = atan(1) * 4;
	float angleInc = (pi/2.0f) / (smooth - 1);

	sf::Vector2f currStartPt = m_position;

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
	currStartPt.x = (m_position.x + m_size.x) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi/2.0f) - angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y -= radius * sin(currAngle);
		this->sprite.setPoint(i + smooth, currPt);
	}
	
	// bottom right corner
	currStartPt.y = (m_position.y + m_size.y) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		this->sprite.setPoint(i + (smooth*2), currPt);
	}

	// bottom left corner
	currStartPt.x = (m_position.x + radius);
	currStartPt.y = (m_position.y + m_size.y) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi/2.0f) - angleInc * i;
		currPt.x -= radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		this->sprite.setPoint(i + (smooth*3), currPt);
	}

	this->sprite.setOutlineThickness(2);
	this->sprite.setPosition(m_position);

}