#include "GuiStyle.hpp"

GuiStyle::GuiParams::GuiParams(
	FontPtr font,
	TexPtr texture,
	sf::Color textColor,
	sf::Color bgColor,
	sf::Color outlineColor
) : 
	m_font(font),
	m_texture(texture),
	m_textColor(textColor),
	m_bgColor(bgColor),
	m_outlineColor(outlineColor)
{}

GuiStyle::GuiStyle(
	Gui& gui,
	Resources& resources,
	std::string id
) :
	m_id(id)
{
	// TODO: THIS IS DEFAULTIST TRASH. MAKE THIS GENERAL OR SUFFER THE KILLSWITCH OF THE MASSES.
	m_stateParams[GUISTATE_ENABLED]    = GuiParams(resources.getFont("Assets/default_font.ttf"), nullptr, sf::Color::White, sf::Color(66,66,70), sf::Color(77,77,80));
	m_stateParams[GUISTATE_CLICKED]    = GuiParams(resources.getFont("Assets/default_font.ttf"), nullptr, sf::Color::Black, sf::Color(230, 230, 230), sf::Color(255, 255, 255));
	m_stateParams[GUISTATE_HOVER]      = GuiParams(resources.getFont("Assets/default_font.ttf"), nullptr, sf::Color::White, sf::Color(77, 77, 80), sf::Color(77, 77, 80));
	m_stateParams[GUISTATE_DISABLED]   = GuiParams(resources.getFont("Assets/default_font.ttf"), nullptr, sf::Color::White, sf::Color(66, 66, 70), sf::Color(77, 77, 80));
	m_stateParams[GUISTATE_FOCUS]      = GuiParams(resources.getFont("Assets/default_font.ttf"), nullptr, sf::Color::White, sf::Color(66, 66, 70), sf::Color(77, 77, 80));
}

std::string GuiStyle::getId() 
{
	return m_id;
}

FontPtr GuiStyle::getStateFont(GuiState state) 
{
	return m_stateParams[state].m_font;
}


TexPtr GuiStyle::getStateTexture(GuiState state) 
{
	return m_stateParams[state].m_texture;
}

sf::Color* GuiStyle::getBgColor(GuiState state) 
{
	return &(m_stateParams[state].m_bgColor);
}

sf::Color* GuiStyle::getOutlineColor(GuiState state)
{
	return &(m_stateParams[state].m_outlineColor);
}