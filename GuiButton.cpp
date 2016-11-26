#include "GuiButton.hpp"
#include "SFML\Graphics.hpp"

GuiButton::GuiButton() {
	m_id = "";
	m_position = sf::Vector2i(0, 0);
}

void GuiButton::draw(const float dt, sf::RenderWindow& win) {

	win.draw(this->m_sprite);

}

void GuiButton::update(const float dt) {

	

}

GuiButton::GuiButton(sf::Vector2i pos) {

	this->m_position = pos;

	this->m_sprite = sf::RectangleShape(sf::Vector2f(120, 50));

}