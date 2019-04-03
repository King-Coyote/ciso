#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "TerrainTile.hpp"
#include "ECS/Entity.hpp"
#include "Camera.hpp"
#include "NavMesh.hpp"

namespace ci {

class ResourceManager;

class Area {
public:
	Area(ResourceManager& resourceManager, unsigned width, unsigned height);

	void update(const float dt);
	void draw(const float dt, sf::RenderWindow& window);
private:
	NavMesh navMesh;
	Camera camera;
};

}