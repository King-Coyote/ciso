#include "Game.hpp"
#include "ResourceManager.hpp"

namespace ci {

Game::Game(ResourceManager& resourceManager) {
    this->areas.push_back(Area(resourceManager, 20, 20));
}

void Game::update(const float dt) {

}

void Game::draw(const float dt, sf::RenderWindow& window) {
    for (auto& area : this->areas) {
        area.draw(dt, window);
    }
}


}