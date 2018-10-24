#include "TerrainTile.hpp"

namespace ci {

TerrainTile::TerrainTile(const sf::Texture& texture, const sf::IntRect rect) :
    sprite(sf::Sprite(texture, rect))
{}

void TerrainTile::draw(const float dt, sf::RenderWindow& window) {
    window.draw(this->sprite);
}

}