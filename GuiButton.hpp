#pragma once

#include "GuiObject.hpp"
#include "Gui.hpp"

class GuiButton : public GuiObject {

private:
	sf::Text m_text;
	sf::RectangleShape m_sprite;

public:

	GuiButton(sf::Vector2i pos);
//	GuiButton(sf::String text);
	//GuiButton(sf::String text, sf::RectangleShape sprite);
	//GuiButton(sf::RectangleShape sprite);

	void draw(const float dt);
	void update(const float dt);

};