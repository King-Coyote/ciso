#include "Resources.hpp"

FontPtr Resources::getFont(std::string filename, bool keep) {

	sf::Font font;

	if (m_fontMap.count(filename) > 0) {
		return m_fontMap[filename];
	}

	if (font.loadFromFile(filename)) {
		FontPtr ptr = FontPtr(&font);
		if (keep) {
			m_fontMap[filename] = ptr;
		}
		return ptr;
	} else {
		// TODO: needs to throw exception or something here my dude
		return nullptr;
	}

}