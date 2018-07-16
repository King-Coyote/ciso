#pragma once

#include <unordered_map>
#include <memory>
#include "GuiStyle.hpp"

namespace std {
// This allows me to combine the hashes of the style elements
// basically a direct ripoff of Boost's combine hash method
template<>
struct hash<ci::GuiStyle> {
    std::size_t operator()(const ci::GuiStyle& k) const {
        using std::size_t;
        using std::hash;
        size_t seed = 0;
        hash<int> intHasher;
        seed ^= intHasher(k.getBgColor().toInteger()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= intHasher(k.getFgColor().toInteger()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= intHasher(k.getOutlineColor().toInteger()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= intHasher(k.getOutlineThickness()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;

    }
};
template<>
struct equal_to<ci::GuiStyle> {
    bool operator()(const ci::GuiStyle& lhs, const ci::GuiStyle& rhs) const {
    return (lhs.outlineColor == rhs.outlineColor
            && lhs.outlineThickness == rhs.outlineThickness
            && lhs.bgColor == rhs.bgColor
            && lhs.fgColor == rhs.fgColor);
    }
};
}

namespace ci {

class StyleMap {
public:
    std::weak_ptr<GuiStyle> getStyle(const mun::Table& t);
private:
    std::unordered_map<GuiStyle, shared_ptr<GuiStyle>> map;

};

}