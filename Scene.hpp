#pragma once

#include <vector>

#include "SFML\Graphics.hpp"
#include "GameObject.hpp"

class Scene : public GameObject {

public:

	std::vector<GameObject*> sceneObjects;

	sf::Font font; //DELETEME

	Scene();
	~Scene();

	void update(const float dt);
	void draw();

};
