#include "ComponentContainer.hpp"

using namespace std;

namespace ci {

ComponentContainer::ComponentContainer(const unsigned numEntities) :
    compIndexes({
        {"movement", ComponentIndex::MOVEMENT},
        {"appearance", ComponentIndex::APPEARANCE},
        {"transform", ComponentIndex::TRANSFORM}
    })
{
    this->entities = ccontainer<Entity>(numEntities);
    this->transformComponents = ccontainer<ComponentTransform>(numEntities);
	this->appearanceComponents = ccontainer<ComponentAppearance>(numEntities);
	this->movementComponents = ccontainer<ComponentMovement>(numEntities);

    for (int i = 0; i<numEntities; i++) {
        this->freeIndices.push_back(i);
    }
}

bool ComponentContainer::createEntity(mun::Table& t) {
    unsigned freeIndex = this->freeIndices.back();
    this->freeIndices.pop_back();

    for (auto& key : t.keys()) {
        switch(this->compIndexes[key]) {
        case ComponentIndex::MOVEMENT:
            this->movementComponents.emplace(
                movementComponents.begin() + freeIndex, 
                ComponentMovement(t.get<mun::Table>("movement"))
            );
            break;
        case ComponentIndex::APPEARANCE:
            this->appearanceComponents.emplace(
                appearanceComponents.begin() + freeIndex, 
                ComponentMovement(t.get<mun::Table>("appearance"))
            );
            break;
        case ComponentIndex::TRANSFORM:
            this->transformComponents.emplace(
                transformComponents.begin() + freeIndex, 
                ComponentMovement(t.get<mun::Table>("transform"))
            );
            break;
        default:
            break;
        }
    }
}

}

