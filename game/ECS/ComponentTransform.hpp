#pragma once

namespace ci {

class ComponentTransform {
public:
    ComponentTransform(mun::Table& t);

    float x;
    float y;
    float z;
    unsigned r; // rotation cardinal: 0 for straight up, then 1 for NE, 2 for E, so on.
};

}
