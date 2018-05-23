#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "AbstractResource.hpp"

namespace ci {

template<typename T>
class Resource : public AbstractResource {
public:
    bool load(const std::string& filename) override;
    T* get() {
        return &data;
    }

private:
    T data;
};

}