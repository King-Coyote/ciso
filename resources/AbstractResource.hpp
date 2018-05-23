#pragma once

#include <string>

namespace ci {
    class AbstractResource;
}

class ci::AbstractResource {
public:
    virtual bool load(const std::string& filename) = 0;
    bool isLoaded() {
        return this->loaded;
    }

private:
    bool loaded;
};