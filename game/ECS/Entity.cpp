#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "luavm/Table.hpp"

namespace ci {

void Entity::update(float dt) {

}

void Entity::instantiate(mun::Table& t, ci::ResourceManager& resourceManager) {
    
    // mun::Table tAppearance  = t.get<mun::Table>("appearance", mun::Table());
    // mun::Table tMovement    = t.get<mun::Table>("movement", mun::Table());

    // if (tAppearance) {
    //     this->appearance = ComponentAppearance(tAppearance, resourceManager);
    // }
    // if (tMovement) {
    //     this->movement = ComponentMovement(tMovement);
    // }

    for (auto& key : t.keys()) {
        // call some indexed function for this key type - mek static ordered map of vals kunt
        this->addComponent(key, t.get<mun::Table, const char*>(key.c_str()));
    }

    this->instanced = true;
}

void Entity::addComponent(const std::string& componentKey, const mun::Table& componentTable) {
    
}

void Entity::modComponent(const std::string& componentKey, const mun::Table& componentTable) {

}


}