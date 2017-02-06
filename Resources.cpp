#include "Resources.hpp"

FontPtr Resources::getFont(std::string filename, bool keep) {

	if (m_fontMap.count(filename) > 0) {
		return m_fontMap[filename];
	}

	sf::Font* fontRaw = new sf::Font();

	if (fontRaw->loadFromFile(filename)) {
		FontPtr shared = FontPtr(fontRaw);
		if (keep) {
			m_fontMap[filename] = shared;
		}
		return shared;
	} else {
		// TODO: needs to throw exception or something here my dude
		return nullptr;
	}

}

TexPtr Resources::getTexture(std::string filename, bool keep, sf::IntRect area) {

	sf::Texture texture;

	if (m_texMap.count(filename) > 0) {
		return m_texMap[filename];
	}

	if (texture.loadFromFile(filename)) {
		TexPtr ptr = TexPtr(&texture);
		if (keep) {
			m_texMap[filename] = ptr;
		}
		return ptr;
	} else {
		return nullptr;
	}

}