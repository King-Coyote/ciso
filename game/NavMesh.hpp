#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "Thor/Shapes.hpp"

namespace ci {

class NavMesh {
public:
    NavMesh() {}
    NavMesh(std::vector<sf::Vector2f>& pts);

    void draw(const float dt, sf::RenderWindow& window);
private:
    std::vector<std::unique_ptr<sf::Drawable>> objs;
};

}