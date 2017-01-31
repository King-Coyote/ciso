#include <memory>

#include "SFML\Graphics.hpp"
#include "GuiObject.hpp"
#include "Resources.hpp"

class Gui;

typedef std::shared_ptr<sf::Font> FontPtr;
typedef std::shared_ptr<sf::Texture> TexPtr;

class GuiStyle {

private:

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

private:

	std::string m_id;
	GuiParams m_stateParams[GUISTATE_NUM_STATES];

public:

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

};