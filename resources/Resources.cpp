#include "Resources.hpp"

FontPtr Resources::getFont(std::string filename, bool keep) {

	if (m_fontMap.count(filename) > 0) {
		return m_fontMap[filename];
	}

	sf::Font* fontRaw = new sf::Font();

	if (fontRaw->loadFromFile(filename)) {
		FontPtr fontShared = FontPtr(fontRaw);
		if (keep) {
			m_fontMap[filename] = fontShared;
		}
		return fontShared;
	} else {
		// TODO: needs to throw exception or something here my dude
		return nullptr;
	}

}

TexPtr Resources::getTexture(std::string filename, bool keep, sf::IntRect area) {

	if (m_texMap.count(filename) > 0) {
		return m_texMap[filename];
	}

	sf::Texture* texRaw = new sf::Texture();

	if (texRaw->loadFromFile(filename)) {
		TexPtr texShared = TexPtr(texRaw);
		if (keep) {
			m_texMap[filename] = texShared;
		}
		return texShared;
	} else {
		return nullptr;
	}

}