#include "GuiButton.hpp"
#include "SFML\Graphics.hpp"

void GuiButton::draw(const float dt) {



}

void GuiButton::update(const float dt) {

	

}

GuiButton::GuiButton(sf::Vector2i pos) {

	this->m_position = pos;

	this->m_sprite = sf::RectangleShape(sf::Vector2f(120, 50));

}