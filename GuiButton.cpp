#include <iostream>
#include <cmath>

#include "GuiButton.hpp"
#include "SFML\Graphics.hpp"
#include "GuiStyle.hpp"

GuiButton::GuiButton() {
	m_id = "";
	this->setPos(sf::Vector2f(150.0f,150.0f));
	m_currentState = ENABLED;
}

GuiButton::GuiButton(
	std::string id, sf::Vector2f pos, sf::Vector2f size,
	std::string defaultGuiStyleName, 
	std::string text,
	EventQueue* mainQ
) {

	m_size = size;
	m_id = id;
	createPolygon();
	this->setPos(pos);

	for (ButtonState state = ENABLED; state < NUM_BUTTON_STATES; state = ButtonState(state + 1)) {
		m_stateStyleIds[state] = defaultGuiStyleName;
	}

	m_mainQ = mainQ;

	m_currentState = ENABLED;

}

ButtonState GuiButton::changeState(ButtonState destinationState) {

	ButtonState lastState = m_currentState;

	//if (m_styleAtlas == nullptr || m_styleAtlas->count(m_stateStyleIds[m_currentState]) < 1) {
	//	return lastState;
	//}

	m_currentState = destinationState;

	// from the statStyleIds array, get string for current state's styleid. Then from that, look in styleatlas
	// pointer for style with that id. Then from that style, get a reference to the required font.
//	m_text.setFont(m_styleAtlas->at(m_stateStyleIds[m_currentState]).getFont());

	return lastState;
	
}

void GuiButton::draw(const float dt, sf::RenderWindow& win) {

	win.draw(m_sprite);
	win.draw(m_text);

}

void GuiButton::update(const float dt) {

	

}

void GuiButton::setPos(sf::Vector2f pos) {
	m_position = pos;
	m_sprite.setPosition(pos);
	m_text.setPosition(pos);
}

void GuiButton::setStateStyleId(ButtonState state, std::string newId) {
	m_stateStyleIds[state] = newId;
}

bool GuiButton::pointInsideBounds(sf::Vector2i point) {
	return (this->m_sprite.getGlobalBounds().contains(point.x, point.y));
}

void GuiButton::onMouseEntered() {
	if (m_currentState == ENABLED) {
		this->changeState(HOVER);
	}
}

void GuiButton::onMouseExited() {
	if (m_currentState == HOVER || m_currentState == CLICKED) {
		this->changeState(ENABLED);
	}
}

void GuiButton::onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	if (m_currentState == HOVER) {
		this->changeState(CLICKED);
	}

}

void GuiButton::onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	if (m_currentState == CLICKED) {
		this->changeState(HOVER);
		if (m_mainQ != nullptr) {
			std::shared_ptr<EventGuiButtonClicked> ptr(new EventGuiButtonClicked(m_id, mousePos));
			m_mainQ->postEvent(ptr);
		}
	}

}

void GuiButton::createPolygon() {

	float radius = 5.0f;
	int smooth = 5;
	if (smooth <= 2) { return; }
	float pi = atan(1) * 4;
	float angleInc = (pi/2.0f) / (smooth - 1);

	sf::Vector2f currStartPt = m_position;

	m_sprite = sf::ConvexShape(4*smooth);

	m_sprite.setPointCount(smooth*4);

	// top left corner
	currStartPt.x += radius;
	currStartPt.y += radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = angleInc * i;
		currPt.x -= radius * cos(currAngle);
		currPt.y -= radius * sin(currAngle);
		m_sprite.setPoint(i, currPt);
	}

	// top right corner
	currStartPt.x = (m_position.x + m_size.x) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi/2.0f) - angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y -= radius * sin(currAngle);
		m_sprite.setPoint(i + smooth, currPt);
	}
	
	// bottom right corner
	currStartPt.y = (m_position.y + m_size.y) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		m_sprite.setPoint(i + (smooth*2), currPt);
	}

	// bottom left corner
	currStartPt.x = (m_position.x + radius);
	currStartPt.y = (m_position.y + m_size.y) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi/2.0f) - angleInc * i;
		currPt.x -= radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		m_sprite.setPoint(i + (smooth*3), currPt);
	}

	m_sprite.setOutlineColor(sf::Color::Red);
	m_sprite.setOutlineThickness(2);
	m_sprite.setPosition(m_position);

}