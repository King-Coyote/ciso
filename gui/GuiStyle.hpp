#pragma once

#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"

namespace ci {

class GuiStyle {
    friend std::equal_to<GuiStyle>;
public:
    GuiStyle() {}
    GuiStyle(const mun::Table& t);

    sf::Color   getBgColor() const;
    sf::Color   getFgColor() const;
    sf::Color   getOutlineColor() const;
    unsigned    getOutlineThickness() const;
private:
    sf::Color   bgColor;
    sf::Color   fgColor;
    sf::Color   outlineColor;
    unsigned    outlineThickness;
};

}