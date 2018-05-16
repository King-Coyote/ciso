#pragma once

#include <map>
#include <memory>

#include "SFML/Graphics.hpp" 

typedef std::shared_ptr<sf::Font> FontPtr;
typedef std::shared_ptr<sf::Texture> TexPtr;

class Resources {

private:

	// string is filename
	std::map<std::string, FontPtr> m_fontMap;
	std::map<std::string, TexPtr> m_texMap;

public:
	
	FontPtr getFont(std::string filename, bool keep = false);
	TexPtr getTexture(std::string filename, bool keep = false, sf::IntRect area = sf::IntRect());

};