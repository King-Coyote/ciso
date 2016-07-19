#pragma once

#include <string>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

class GuiWidget : public sf::Transformable, public sf::Drawable {

private:

	bool isVisible;

	std::string id;

public:

	// switch isVisible and return whether widget was hidden or not.
	bool hide();
	bool show();

	virtual void draw(sf::RenderWindow* win) = 0;

};