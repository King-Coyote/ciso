#include "GuiStyle.hpp"

GuiStyle::GuiStyle(Gui& gui,
				std::string fontName = "DEFAULT_FONT",
				std::string textureName = "DEFAULT_TEXTURE",
				sf::Color textColor = sf::Color::White) {

	m_font = gui.getFontPtr(fontName);
	m_texture = gui.getTexturePtr(textureName);
	m_textColor = textColor;

}