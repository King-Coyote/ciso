#pragma once

#include <vector>
#include "SFML/Window.hpp"
#include "Entity.hpp"
#include "Area.hpp"

namespace ci {

class ResourceManager;

class Game {
public:
	Game(ResourceManager& resourceManager);
	void update(const float dt);
	void draw(const float dt, sf::RenderWindow& window);
private:
	std::vector<Entity> entities;
	std::vector<Area> 	areas;
};

}