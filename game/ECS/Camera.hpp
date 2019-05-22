#pragma once

#include <cstddef>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Transform.hpp"

namespace ci {

class Camera {
public:
    ci::Transform screenCoordsToTransform(const sf::Vector2f& mouseCoords) const;
    void move(const ci::Transform& transform);
    
    ci::Transform transform;
};

}