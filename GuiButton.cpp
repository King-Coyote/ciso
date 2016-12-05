#include <iostream>

#include "GuiButton.hpp"
#include "SFML\Graphics.hpp"

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
	this->m_currentState = destinationState;
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

bool GuiButton::pointInsideBounds(sf::Vector2i point) {
	return (this->m_sprite.getGlobalBounds().contains(point.x, point.y));
}

void GuiButton::onMouseEntered() {
	this->changeState(HOVER)
}

