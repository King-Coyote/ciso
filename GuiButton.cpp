#include "GuiButton.hpp"

	//sf::RectangleShape sprite; //TODO replace this with an actual sprite
//	sf::Text text;

//	bool isPressed;
//	void draw(sf::RenderTarget& target, sf::RenderStates states);

void GuiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(sprite);
	target.draw(text);

}

GuiButton::GuiButton(float width, float height, float x, float y) {

	this->width = width;
	this->height = height;

	this->setPosition(sf::Vector2f(x, y));

}

GuiButton::~GuiButton() {


}