#pragma once

#include "SFML/Graphics.hpp"

// TODO if this class has no functionality other than drawing, just replace it with a sprite

namespace ci {

class TerrainTile {
public:
    TerrainTile(const sf::Texture& texture, const sf::IntRect rect);
    void draw(const float dt, sf::RenderWindow& window);
private:
    sf::Sprite sprite;
};

}