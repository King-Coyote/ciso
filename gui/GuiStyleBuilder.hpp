#pragma once

#include "luavm/Table.hpp"
#include "GuiStyle.hpp"

namespace ci {

class GuiStyleBuilder {
public:

    GuiStyle build(const mun::Table& t) const;
private:

};

}