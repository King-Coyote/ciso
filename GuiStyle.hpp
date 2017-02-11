#pragma once

#include <memory>
#include <exception>

#include "SFML\Graphics.hpp"
#include "GuiObject.hpp"
#include "Resources.hpp"

class Gui;

typedef std::shared_ptr<sf::Font> FontPtr;
typedef std::shared_ptr<sf::Texture> TexPtr;

class GuiStyle {

public: // METHODS

	GuiStyle(
		Gui& gui,
		Resources& resources,
		std::string id
	);

	std::string getId();

	FontPtr getStateFont(GuiState state);
	TexPtr getStateTexture(GuiState state);
	sf::Color* getBgColor(GuiState state);
	sf::Color* getOutlineColor(GuiState state);
	sf::Color* getTextColor(GuiState state);

	// Guaranteed object acquisition methods
	// these must return a ref of the specified type, otherwise
	// they throw a motherfuckin exception biiiiiiiiich
	FontPtr getGuaranteedFont();

private: // CLASSES

	// this is the class that holds the pointers to the various qualities
	// used by guiObjects. There is one of these for each possible state for a gui obj.
	class GuiParams {
	public:

		FontPtr m_font;
		TexPtr m_texture;
		sf::Color m_textColor;
		sf::Color m_bgColor;
		sf::Color m_outlineColor;

		// maybe change this later for data-driven initialisation?
		GuiParams() {}
		GuiParams(
			FontPtr font,
			TexPtr texture,
			sf::Color textColor,
			sf::Color bgColor,
			sf::Color outlineColor
		);
		~GuiParams() {};
	};

	// the guaranteed resources MUST be available, otherwise the GUI system ain't gone work.
	// This is because SFML objects require references when constructing.
	class GuaranteedResourceException : public std::exception {
		virtual const char* what() const throw()
		{
			return "Guaranteed resource was unable to be loaded!";
		}
	};

private: // MEMBERS

	// these are objects that can be used if a reference is required but the current
	// guiStyle does not have any pointers to one for that object type.
	static FontPtr fallbackFont;

	std::string m_id;
	GuiParams m_stateParams[GUISTATE_NUM_STATES];

};