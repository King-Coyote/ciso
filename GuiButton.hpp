#pragma once

#include "SFML/Graphics.hpp"
#include "GuiWidget.hpp"

class GuiButton : public GuiWidget {

private:

	sf::RectangleShape sprite; //TODO replace this with an actual sprite
	sf::Text text;
	float width, height;

public:

	bool isPressed;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setPosition(sf::Vector2f pos);

	GuiButton(float width, float height, float x, float y);
	~GuiButton();

};
