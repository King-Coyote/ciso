#pragma once

#include <memory>
#include "luavm/Table.hpp"
#include "NavMesh.hpp"
#include "Component.hpp"

namespace ci {

class ComponentSpace : public Component {
public:
    ComponentSpace();
    ComponentSpace(mun::Table& t);
    ComponentSpace(mun::Table&& t);

    std::unique_ptr<NavMesh> navMesh;
    std::vector<std::size_t> containedRefs;
    // std::vector<TerrainObject> terrainz
    
};

}
