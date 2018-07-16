#include "StyleMap.hpp"

namespace ci {

std::weak_ptr<GuiStyle> StyleMap::getStyle(const mun::Table& t) {
    GuiStyle style = GuiStyle(t);
    if (this->map.count(style) == 0) {
        this->map[style] = shared_ptr<GuiStyle>(new GuiStyle(style));
    }
    return weak_ptr<GuiStyle>(this->map[style]);
}

}