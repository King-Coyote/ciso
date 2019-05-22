#pragma once

#include <cstddef>
#include "luavm/Table.hpp"
#include "Component.hpp"
#include "Transform.hpp"

namespace ci {

class ComponentTransform : public Component {
public:
    ComponentTransform();
    ComponentTransform(mun::Table& t);
    ComponentTransform(mun::Table&& t);
    ComponentTransform(const Transform& rawTransform);

    ComponentTransform& operator=(const Transform& rawTransform);

    Transform transform;
};

}
