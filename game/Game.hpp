#pragma once

#include <vector>
#include "SFML/Window.hpp"
#include "Entity.hpp"
#include "Area.hpp"

namespace ci {

class ResourceManager;

template <typename T>
using ComponentContainer = std::vector<T>;

class Game {
public:
	Game(ResourceManager& resourceManager);
	void update(const float dt);
	void draw(const float dt, sf::RenderWindow& window);
private:
	ci::ComponentContainer<Entity> entities;
	ci::ComponentContainer<Area> 	areas;
	// GAME PARAMETERS
	unsigned	numEntities = 1;
};

}