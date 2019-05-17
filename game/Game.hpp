#pragma once

#include <vector>
#include <map>
#include "SFML/Window.hpp"
#include "luavm/State.hpp"
#include "luavm/Table.hpp"
#include "ECS/Entity.hpp"
#include "Area.hpp"
#include "NavMesh.hpp"
#include "EventHandler.hpp"
#include "Event.hpp"
// TODO put all components into a header file for convenience
#include "ECS/ComponentAppearance.hpp"
#include "ECS/ComponentMovement.hpp"
#include "ECS/ECSSystem.hpp"

namespace ci {

class ResourceManager;
class Scripting;

class Game : public EventHandler {
public:
	Game(ResourceManager& resourceManager, Scripting& scripting);

	void update(const float dt);
	void draw(const float dt, sf::RenderWindow& window);
private:

	ci::ECSSystem ecsSystem;
	std::vector<Area> areas;

	// GAME PARAMETERS
	unsigned			numEntities;
	
	ResourceManager*	resourceManager;

	//DELETEME
	std::unique_ptr<NavMesh> navMesh;

	// Event handling
	void onMouseRelease(EventInput* ei);

	// LUA BINDINGS
	int lua_createEntity(lua_State* L);
	int lua_destroyEntity(lua_State* L);
	int lua_addComponent(lua_State* L);
	int lua_removeComponent(lua_State* L);
};

}