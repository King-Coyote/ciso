#pragma once

#include "GuiObject.hpp"
#include "GuiStyle.hpp"

class GuiText : public GuiObject {

public: // METHODS

	GuiText(
		std::string id,
		sf::Vector2f position,
		sf::Vector2f size,
		std::string styleId,
		std::string text,
		int textSize
	);

	std::string setText(std::string newString);

	// OVERRIDES
	void setPos(sf::Vector2f newPos);
	void setSize(sf::Vector2f newSize);

	void draw(const float dt, sf::RenderWindow& win);
	void update(const float dt);

private: // MEMBERS

	sf::Text text;
	std::string textString;
	int textSize;

private: // METHODS

	void initialiseVisualElements();
	void changeToStateStyle(GuiState state);

};
