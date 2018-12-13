#include "Game.hpp"
#include "ResourceManager.hpp"

namespace ci {

Game::Game(ResourceManager& resourceManager) {
    // DELETEME defaultist traysh
    this->areas.push_back(Area(resourceManager, 20, 20));
    this->entities = ci::ComponentContainer<Entity>(this->numEntities, Entity());
}

void Game::update(const float dt) {
    // also need to update all non-area objects
    for (auto& area : this->areas) {
        area.update(dt);
    }
}

void Game::draw(const float dt, sf::RenderWindow& window) {
    for (auto& area : this->areas) {
        area.draw(dt, window);
    }
}


}