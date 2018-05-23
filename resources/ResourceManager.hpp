#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "AbstractResource.hpp"
#include "Resource.hpp"

typedef std::unique_ptr<ci::AbstractResource> resourcePtr;

namespace ci {
    class ResourceManager;
}

class ci::ResourceManager {
public:
    template<typename T>
    inline T* getResource(std::string name) {
        if (resources.count(name) == 0) {
            resources[name] = std::unique_ptr<Resource<T>>(new Resource<T>());
        }
        if (!resources[name]->load(name)) {
            throw std::runtime_error("file not found");
        }
        Resource<T>* ptr = dynamic_cast<Resource<T>*>(resources[name].get());
        if (ptr == 0) {
            throw std::runtime_error("resource not able to be cast!");
        }
        return ptr->get();
    }

private:
    std::unordered_map<std::string, resourcePtr> resources;
};