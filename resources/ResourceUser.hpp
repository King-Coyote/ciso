#pragma once

#include "Resources.hpp"

class ResourceUser {
public:
    virtual void SetResourceManager(const Resources& r);
protected:
    Resources& resourceManager;
};