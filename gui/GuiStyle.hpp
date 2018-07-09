#pragma once

#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"

namespace ci {

class GuiStyle {
public:
    GuiStyle(const mun::Table& t);

    sf::Color   getBgColor() const;
    sf::Color   getFgColor() const;
    sf::Color   getOutlineColor() const;
    unsigned    getOutlineThickness() const;
    bool        operator==(const GuiStyle& b) const;
private:
    sf::Color   bgColor;
    sf::Color   fgColor;
    sf::Color   outlineColor;
    unsigned    outlineThickness;
};

}