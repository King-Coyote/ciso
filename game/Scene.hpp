#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

class GameObject;

class Scene {

public:
	std::vector<GameObject*> sceneObjects;

	Scene();
	~Scene();

	void update(const float dt);
	void draw(const float dt);

};
