#include "Area.hpp"
#include "Gui.hpp"
#include "ResourceManager.hpp"

namespace ci {

Area::Area(ResourceManager& resourceManager, unsigned width, unsigned height) {
    this->tileAtlas = resourceManager.getResource<sf::Texture>("tileatlas.png");
}

void Area::update(const float dt) {

}   

void Area::draw(const float dt, sf::RenderWindow& window) {
    for (auto& tile : this->terrain) {
        tile.draw(dt, window);
    }
}

}