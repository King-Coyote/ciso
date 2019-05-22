#include "Game.hpp"
#include "ResourceManager.hpp"
#include "Scripting.hpp"

using namespace std;

namespace ci {

Game::Game(ResourceManager& resourceManager, Scripting& scripting) :
    resourceManager(&resourceManager),
    EventHandler({EventType::SFML_INPUT}),
    ecsSystem(ECSSystem(10, resourceManager)) // TODO get rid of the 100 - defaultist traysh
{
    // DELETEME defaultist traysh
    //this->areas.push_back(Area(resourceManager, 20, 20));

    //DELETEME
    // vector<sf::Vector2f> pts = {
    //     sf::Vector2f(0, 0),
    //     sf::Vector2f(35, 0),
    //     sf::Vector2f(35, 70),
    //     sf::Vector2f(55, 70),
    //     sf::Vector2f(55, 0),
    //     sf::Vector2f(75, 0),
    //     sf::Vector2f(75, 50),
    //     sf::Vector2f(100, 50),
    //     sf::Vector2f(100, 60),
    //     sf::Vector2f(75, 60),
    //     sf::Vector2f(75, 110),
    //     sf::Vector2f(100, 110),
    //     sf::Vector2f(100, 140),
    //     sf::Vector2f(55, 140),
    //     sf::Vector2f(55, 110),
    //     sf::Vector2f(0, 110)
    // };
    // for (auto& v : pts) {
    //     v *= 3.0f;
    // }
    // this->navMesh = unique_ptr<NavMesh>(new NavMesh(pts));

    // set up game scripting bindings (need pointer in class?)
    scripting.getState().bindGlobalClass("Game", this)
    .def<&Game::lua_createEntity>("createEntity")
    .def<&Game::lua_destroyEntity>("destroyEntity")
    .def<&Game::lua_addComponent>("addComponent")
    .def<&Game::lua_removeComponent>("removeComponent")
    .def<&Game::lua_moveCamera>("moveCamera");

    scripting.getState().runString(R"(
        local area = Game:createEntity{
            space = {
                level = 100
            }
        }
        Game:moveCamera{
            x = 0,
            y = 0,
            areaRef = area
        }
        Game:createEntity{
            transform = {
                x = 10,
                y = 10,
                areaRef = area
            },
            appearance = {
                level = 100,
                filename = "sprites/elminster_single.png"
            }
        }
    )");
    
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
    // this->navMesh->draw(dt, window);
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

int Game::lua_moveCamera(lua_State* L) {
    mun::Table t(L, 2);
    this->ecsSystem.moveCamera(ci::Transform(t));
    return 0;
}


}