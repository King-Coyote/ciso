#pragma once

#include <vector>

#include "Graphics.hpp"
#include "GameObject.hpp"

class Scene : public GameObject {

public:

	std::vector<GameObject*> sceneObjects;

	Scene();
	~Scene();

	void update(const float dt);
	void draw(const float dt);

};
