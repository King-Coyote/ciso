#pragma once

#include <string>
#include <lua.hpp>

using namespace std;

class Scripting {
public:
    Scripting();
    ~Scripting();

    void runScript(string filename);
    int scriptEvent(lua_State* L);

private:
    lua_State* l;

};