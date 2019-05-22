#include "Camera.hpp"

namespace ci{

ci::Transform Camera::screenCoordsToTransform(const sf::Vector2f& mouseCoords) const {
    return Transform(mouseCoords.x, mouseCoords.y, this->transform.areaRef);
}

}