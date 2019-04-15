#include "Game.hpp"
#include "ResourceManager.hpp"
#include "Scripting.hpp"

using namespace std;

namespace ci {

Game::Game(ResourceManager& resourceManager, Scripting& scripting, EventQueue& eventQueue) :
    resourceManager(&resourceManager),
    EventHandler({EventType::SFML_INPUT}),
    ecsSystem(ECSSystem(10, resourceManager)) // TODO get rid of the 100 - defaultist traysh
{
    // DELETEME defaultist traysh
    //this->areas.push_back(Area(resourceManager, 20, 20));

    //DELETEME
    vector<sf::Vector2f> pts = {
        sf::Vector2f(75,100),
        sf::Vector2f(110,100),
        sf::Vector2f(110,170),
        sf::Vector2f(130,170),
        sf::Vector2f(130,100),
        sf::Vector2f(150,100),
        sf::Vector2f(150,150),
        sf::Vector2f(175,150),
        sf::Vector2f(175,160),
        sf::Vector2f(150,160),
        sf::Vector2f(150,210),
        sf::Vector2f(175,210),
        sf::Vector2f(175,240),
        sf::Vector2f(130,240),
        sf::Vector2f(130,210),
        sf::Vector2f(75,210)
    };
    this->navMesh = unique_ptr<NavMesh>(new NavMesh(pts));

    // set up game scripting bindings (need pointer in class?)
    scripting.getState().bindGlobalClass("Game", this)
    .def<&Game::lua_createEntity>("createEntity")
    .def<&Game::lua_destroyEntity>("destroyEntity")
    .def<&Game::lua_addComponent>("addComponent")
    .def<&Game::lua_removeComponent>("removeComponent");
    
}

void Game::onMouseRelease(EventInput* ei) {
    if (ei->isCaptured()) {
        return;
    }
    // get nearest to click
}

void Game::update(const float dt) {
    this->ecsSystem.update(dt);
}

void Game::draw(const float dt, sf::RenderWindow& window) {
    // DELETEME
    this->navMesh->draw(dt, window);
    this->ecsSystem.draw(dt, window);
}

int Game::lua_createEntity(lua_State* L) {
    mun::Table t(L, 2);
    int index = this->ecsSystem.createEntity(t);
    lua_pushinteger(L, index);
    return 1;
}

int Game::lua_destroyEntity(lua_State* L) {
    int index = lua_tonumber(L, 2);
    this->ecsSystem.destroyEntity(index);
    return 0; //TODO return success of entity deletion?
}

int Game::lua_addComponent(lua_State* L){
    return 1;
}

int Game::lua_removeComponent(lua_State* L){
    return 1;
}


}