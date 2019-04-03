#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"
#include "Components.hpp"
#include "AppearanceSystem.hpp"
#include "MovementSystem.hpp"

template <typename T>
using ccontainer = std::vector<T>;

namespace ci {

class ResourceManager;

/**
 * /brief a class for managing components.
 */
class ECSSystem {
public:

    ECSSystem(const unsigned numEntities, ResourceManager& resourceManager);

    /**
     * /brief create an entity
     * /param t the table of the entity
     * /return index of the newly created entity, -1 if it failed.
     */
    int createEntity(mun::Table& t);
    /**
     * /brief destroy an entity at index
     * /param index the index at which you want to destroy. This is the object ref
     * If this doesn't destroy successfully, you should just crash the program since fully controlling entities
     *  is really an invariant
     */
    void destroyEntity(const unsigned index);

    void update(float dt);
    void draw(float dt, sf::RenderWindow& window);
private:
	// this is to relate component identifier strings to an enum
	enum ComponentIndex {
		APPEARANCE,
        TRANSFORM,
		MOVEMENT
	};

    std::vector<unsigned> freeIndices;

    // containers
	ccontainer<Entity>				entities;
    ccontainer<ComponentTransform>  transformComponents;
	ccontainer<ComponentAppearance> appearanceComponents;
	ccontainer<ComponentMovement>	movementComponents;

    //systems
    AppearanceSystem    systemAppearance;
    MovementSystem      systemMovement;

	std::map<std::string, ECSSystem::ComponentIndex> compIndexes;

    ResourceManager* resourceManager;

};

}
