#pragma once

#include <map>
#include <memory>

#include "SFML\Graphics.hpp"

typedef std::shared_ptr<sf::Font> FontPtr;

class Resources {

private:

	// string is filename
	std::map<std::string, FontPtr> m_fontMap;

public:
	
	FontPtr getFont(std::string filename, bool keep = false);

};