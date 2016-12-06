#include "GuiStyle.hpp"

GuiStyle::GuiStyle(Gui& gui,
				std::string fontName,
				std::string textureName,
				sf::Color textColor) {

	m_font = gui.getFontPtr(fontName);
	m_texture = gui.getTexturePtr(textureName);
	m_textColor = textColor;

}

std::string GuiStyle::getId() {
	return m_id;
}

sf::Font& GuiStyle::getFont() {
	return *m_font;
}