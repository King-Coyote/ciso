#include <iostream>

#include "GuiButton.hpp"
#include "SFML\Graphics.hpp"
#include "GuiStyle.hpp"

GuiButton::GuiButton() {
	m_id = "";
	this->setPos(sf::Vector2f(150.0f,150.0f));
}

GuiButton::GuiButton(std::string id, sf::Vector2f size, sf::Vector2f pos, std::string defaultGuiStyleName, std::string text) {

	m_sprite = sf::RectangleShape(size);
	this->setPos(pos);

	for (ButtonState state = ENABLED; state < NUM_BUTTON_STATES; state = ButtonState(state + 1)) {
		m_stateStyleIds[state] = defaultGuiStyleName;
	}

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
	if (m_currentState == HOVER) {
		this->changeState(ENABLED);
	}
}

