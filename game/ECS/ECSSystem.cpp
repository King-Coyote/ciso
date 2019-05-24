#include "ECSSystem.hpp"
#include "ResourceManager.hpp"

using namespace std;

namespace ci {

ECSSystem::ECSSystem(const unsigned numEntities, ResourceManager& resourceManager) :
    EventHandler({EventType::SFML_INPUT}),
    compIndexes({
        {"movement", ComponentIndex::MOVEMENT},
        {"appearance", ComponentIndex::APPEARANCE},
        {"transform", ComponentIndex::TRANSFORM},
        {"space", ComponentIndex::SPACE}
    }),
    resourceManager(&resourceManager)
{
    this->entities =                ccontainer<Entity>(numEntities);
    this->transformComponents =     ccontainer<ComponentTransform>(numEntities);
	this->appearanceComponents =    ccontainer<ComponentAppearance>(numEntities);
	this->movementComponents =      ccontainer<ComponentMovement>(numEntities);
    this->spaceComponents =         ccontainer<ComponentSpace>(numEntities);

    this->systemMovement = MovementSystem(
        this->movementComponents,
        this->transformComponents,
        this->spaceComponents
    );

    // TODO how to initialise this
    // and probably also DELETEME
    this->camera = ci::Camera();

    for (int i = numEntities - 1; i>=0; --i) {
        this->freeIndices.push_back(i);
    }
}

int ECSSystem::createEntity(mun::Table& t) {
    // TODO shouldn't this be the thing that registers for create entity events?
    unsigned freeIndex = this->freeIndices.back();
    this->freeIndices.pop_back();
    this->entities[freeIndex].instanced = true;

    for (string& key : t.keys()) {
        switch(this->compIndexes[key]) {
        case ComponentIndex::MOVEMENT:
            this->movementComponents.emplace(
                movementComponents.begin() + freeIndex, 
                ComponentMovement(t.get<mun::Table>(key.c_str()))
            );
            break;
        case ComponentIndex::APPEARANCE:
            this->appearanceComponents.emplace(
                appearanceComponents.begin() + freeIndex, 
                ComponentAppearance(t.get<mun::Table>(key.c_str()), *this->resourceManager)
            );
            break;
        case ComponentIndex::TRANSFORM:
            this->transformComponents.emplace(
                transformComponents.begin() + freeIndex, 
                ComponentTransform(t.get<mun::Table>(key.c_str()))
            );
            break;
        case ComponentIndex::SPACE:
            this->spaceComponents.emplace(
                spaceComponents.begin() + freeIndex, 
                ComponentSpace(t.get<mun::Table>(key.c_str()))
            );
        default:
            break;
        }
    }
    return freeIndex;
}

void ECSSystem::destroyEntity(const unsigned index) {
    if (!this->entities[index].instanced) {
        return;
    }
    this->entities[index].instanced = false;
    this->freeIndices.push_back(index);
    
    this->movementComponents.at(index) = ComponentMovement();
    this->appearanceComponents.at(index) = ComponentAppearance();
    this->transformComponents.at(index) = ComponentTransform();
}

void ECSSystem::update(float dt) {
    this->systemAppearance.update(dt, this->appearanceComponents, this->transformComponents);
    this->systemMovement.update(dt);
}

void ECSSystem::draw(float dt, sf::RenderWindow& window) {
    // DELETEME navmeshes shouldn't be drawn obviously
    std::size_t areaRef = this->camera.transform.areaRef;
    this->spaceComponents.at(areaRef).navMesh->draw(dt, window);
    this->systemAppearance.draw(
        dt, 
        window, 
        this->appearanceComponents, 
        this->transformComponents,
        this->camera
    );
}

bool ECSSystem::moveCamera(const ci::Transform& transform) {
    if (this->spaceComponents.at(transform.areaRef).level <= 10) {
        return false;
    }
    this->camera.transform = ci::Transform(transform);
    return true;
}

void ECSSystem::onMouseRelease(EventInput* ei) {
    if (ei->isCaptured()) {
        return;
    }
    if (ei->sfEvent.mouseButton.button == sf::Mouse::Button::Right) {
        // move command
        // TODO before this can work it needs to have some way of getting the location to move to.
        // this needs to be done using the camera object.
        // right now just make it point to the raw location on screen.
        // if (this->selectedEntities.empty()) {
        //     return;
        // }
        sf::Vector2f screenCoords(ei->sfEvent.mouseButton.x, ei->sfEvent.mouseButton.y);
        this->postEvent(new EventGameCommandMove(
            this->selectedEntities, 
            this->camera.screenCoordsToTransform(screenCoords)
        ));
    }
}

}

