#include <memory>

#include "SFML\Graphics.hpp"
#include "Gui.hpp"

class GuiStyle {

private:

	std::shared_ptr<sf::Font> m_font;
	std::shared_ptr<sf::Texture> m_texture;
	sf::Color m_textColor;

public:

	GuiStyle(Gui& gui,
			std::string fontName = "DEFAULT_FONT",
			std::string textureName = "DEFAULT_TEXTURE",
			sf::Color color = sf::Color::White);

};