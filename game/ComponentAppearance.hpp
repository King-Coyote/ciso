#pragma once 

#include "SFML/Graphics.hpp"
#include "Transform.hpp"

namespace ci {

class ComponentAppearance {
public:
    void draw(float dt, sf::RenderWindow& window);
private:
    sf::Sprite sprite;
    Transform position;
};

}