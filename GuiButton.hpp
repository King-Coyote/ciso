#pragma once

#include "GuiObject.hpp"
#include "GuiStyle.hpp"

class GuiButton : public GuiObject {

private:
	sf::Text m_text;
	sf::RectangleShape m_sprite;

public:

	GuiButton();
	GuiButton(std::string id, sf::Vector2f size, sf::Vector2f pos,
			std::string guiStyleName,
			std::string text = "");

	void setPos(sf::Vector2f pos);

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

};