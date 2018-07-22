#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "Entity.hpp"

namespace ci {

class Scene {

public:

	void update(const float dt);
	void draw(const float dt);
private:

};

}