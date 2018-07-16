#include "GuiStyle.hpp"

namespace ci {

GuiStyle::GuiStyle(const mun::Table& t) :
    outlineThickness(t.get<double>("outlineThickness", 0.0))
{
    mun::Table bgColorT = t.get<mun::Table>("bgColor");
    mun::Table fgColorT = t.get<mun::Table>("fgColor");
    mun::Table outlineColorT = t.get<mun::Table>("outlineColor");

    this->bgColor = sf::Color(
        bgColorT.get<int>(1),
        bgColorT.get<int>(2),
        bgColorT.get<int>(3),
        bgColorT.get<int>(4, 255)
    );
    this->fgColor = sf::Color(
        fgColorT.get<int>(1),
        fgColorT.get<int>(2),
        fgColorT.get<int>(3),
        fgColorT.get<int>(4, 255)
    );
    this->outlineColor = sf::Color(
        outlineColorT.get<int>(1),
        outlineColorT.get<int>(2),
        outlineColorT.get<int>(3),
        outlineColorT.get<int>(4)  
    );
}

sf::Color GuiStyle::getBgColor() const {
    return this->bgColor;
}

sf::Color GuiStyle::getFgColor() const {
    return this->fgColor;
}

sf::Color GuiStyle::getOutlineColor() const {
    return this->outlineColor;
}

unsigned GuiStyle::getOutlineThickness() const {
    return this->outlineThickness;
}
}