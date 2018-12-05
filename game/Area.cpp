#include "Area.hpp"
#include "Gui.hpp"
#include "ResourceManager.hpp"

namespace ci {

Area::Area(ResourceManager& resourceManager, unsigned width, unsigned height) {
    //this->tileAtlas = resourceManager.getResource<sf::Texture>("tileatlas.png");
    vector<sf::Vector2f> pts = vector<sf::Vector2f>();
    pts.push_back(sf::Vector2f(20, 20));
    pts.push_back(sf::Vector2f(400, 20));
    pts.push_back(sf::Vector2f(400, 400));
    pts.push_back(sf::Vector2f(20, 400));
    this->navMesh = NavMesh(pts);
}

void Area::update(const float dt) {

}   

void Area::draw(const float dt, sf::RenderWindow& window) {
    navMesh.draw(dt, window);
}

}