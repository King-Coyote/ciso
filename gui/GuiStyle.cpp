#include "GuiStyle.hpp"

namespace ci {

bool GuiStyle::operator==(const GuiStyle& b) const {
    return (this->outlineColor == b.outlineColor
            && this->outlineThickness == b.outlineThickness
            && this->bgColor == b.bgColor
            && this->fgColor == b.fgColor);
}

}

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
} 