#include "GuiButton.hpp"
#include "SFML\Graphics.hpp"

GuiButton::GuiButton() {
	m_id = "";
	this->setPos(sf::Vector2f(150.0f,150.0f));
}

GuiButton::GuiButton(std::string id, sf::Vector2f size, sf::Vector2f pos,
					std::string guiStyleName,
					std::string text = "") {

	m_sprite = sf::RectangleShape(sf::Vector2f(120.0f, 50.0f));
	this->setPos(pos);

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