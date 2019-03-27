#pragma once

#include <vector>
#include "ECS/Components.hpp"
#include "luavm/Table.hpp"

template <typename T>
using ccontainer = std::vector<T>;

namespace ci {

/**
 * /brief a class for managing components.
 */
class ComponentContainer {
public:

    ComponentContainer(const unsigned numEntities);

    /**
     * /brief create an entity
     * /param t the table of the entity
     * /return true if the entity was successfully created, false if it failed.
     */
    bool createEntity(mun::Table& t);
    /**
     * /brief destroy an entity at index
     * /param index the index at which you want to destroy. This is the object ref
     * If this doesn't destroy successfully, you should just crash the program since fully controlling entities
     *  is really an invariant
     */
    void destroyEntity(const unsigned index);
private:
	// this is to relate component identifier strings to an enum
	enum ComponentIndex {
		APPEARANCE,
        TRANSFORM,
		MOVEMENT
	};

    std::vector<unsigned> freeIndices;

	ccontainer<Entity>				entities;
    ccontainer<ComponentTransform>  transformComponents;
	ccontainer<ComponentAppearance> appearanceComponents;
	ccontainer<ComponentMovement>	movementComponents;
	std::map<std::string, ComponentContainer::ComponentIndex> compIndexes;

};

}
