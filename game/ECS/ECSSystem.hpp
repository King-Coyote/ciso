#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"
#include "Components.hpp"
#include "AppearanceSystem.hpp"
#include "MovementSystem.hpp"
#include "EventHandler.hpp"
#include "EventSender.hpp"
#include "Camera.hpp"

template <typename T>
using ccontainer = std::vector<T>;

namespace ci {

class ResourceManager;

/**
 * /brief a class for managing components.
 */
class ECSSystem : public EventHandler, public EventSender {
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

    bool moveCamera(const ci::Transform& transform);

    void update(float dt);
    void draw(float dt, sf::RenderWindow& window);

    // EVENT HANDLERS
    void onMouseRelease(EventInput* ei) override;

private:
	// this is to relate component identifier strings to an enum
	enum ComponentIndex {
		APPEARANCE,
        TRANSFORM,
		MOVEMENT,
        SPACE
	};

    std::vector<unsigned> freeIndices;

    // the current selected entities;
    // TODO remove this defaultist trash
    std::vector<std::size_t> selectedEntities = {1};

    // containers
	ccontainer<Entity>				entities;
    ccontainer<ComponentTransform>  transformComponents;
	ccontainer<ComponentAppearance> appearanceComponents;
	ccontainer<ComponentMovement>	movementComponents;
    ccontainer<ComponentSpace>      spaceComponents;

    //systems
    AppearanceSystem    systemAppearance;
    MovementSystem      systemMovement;

	std::map<std::string, ECSSystem::ComponentIndex> compIndexes;
    ResourceManager* resourceManager;
    ci::Camera camera;

};

}
