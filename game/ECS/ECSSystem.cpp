#include "ECSSystem.hpp"
#include "ResourceManager.hpp"

using namespace std;

namespace ci {

ECSSystem::ECSSystem(const unsigned numEntities, ResourceManager& resourceManager) :
    compIndexes({
        {"movement", ComponentIndex::MOVEMENT},
        {"appearance", ComponentIndex::APPEARANCE},
        {"transform", ComponentIndex::TRANSFORM}
    }),
    resourceManager(&resourceManager)
{
    this->entities =                ccontainer<Entity>(numEntities - 1);
    this->transformComponents =     ccontainer<ComponentTransform>(numEntities - 1);
	this->appearanceComponents =    ccontainer<ComponentAppearance>(numEntities - 1);
	this->movementComponents =      ccontainer<ComponentMovement>(numEntities - 1);

    for (int i = 0; i<numEntities; i++) {
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
        default:
            break;
        }
    }
    return -1;
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
    this->systemAppearance.draw(dt, window, this->appearanceComponents, this->transformComponents);
}


}

