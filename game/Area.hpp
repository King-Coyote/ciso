#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "TerrainTile.hpp"
#include "Entity.hpp"
#include "Camera.hpp"

namespace ci {

class ResourceManager;

class Area {
public:
	Area(ResourceManager& resourceManager, unsigned width, unsigned height);

	void update(const float dt);
	void draw(const float dt, sf::RenderWindow& window);
private:
	std::vector<TerrainTile> terrain;
	// anti analysis paralysis shitposting
	sf::Texture* tileAtlas;
	Camera camera;
};

}