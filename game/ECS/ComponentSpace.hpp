#pragma once

#include "luavm/Table.hpp"
#include "Component.hpp"

namespace ci {

class ComponentSpace : public Component {
public:
    ComponentSpace();
    ComponentSpace(mun::Table& t);
    ComponentSpace(mun::Table&& t);
private:
    // std::vector<TerrainObject> terrainz
    
};

}
