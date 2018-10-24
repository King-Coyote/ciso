#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "AbstractResource.hpp"

#define BASE_RESOURCE_DIR "/home/alex/projects/academy/coyoteiso/assets/" + filename

namespace ci {

template<typename T>
class Resource : public AbstractResource {
public:
    bool load(const std::string& filename) override {
        return this->data.loadFromFile(BASE_RESOURCE_DIR);
    }
    T* get() {
        return &data;
    }

private:
    T data;
};

}