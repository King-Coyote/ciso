
#include <iostream>
#include "Scripting.hpp"

Scripting::Scripting() {
    this->l = luaL_newstate();
    luaL_openlibs(this->l);
}

Scripting::~Scripting() {
    lua_close(this->l);
}

void Scripting::runScript(string filename) {
    if (luaL_loadfile(this->l, filename.c_str()) || lua_pcall(this->l, 0, 0, 0)) {
        cout << "ERROR\n";
    }
    lua_getglobal(this->l, "fuck");
    cout << "Variable fuck had value " << lua_tointeger(this->l, -1) << endl;
}

int Scripting::scriptEvent(lua_State* L) {
    lua_getglobal(L, "eventStr");
    cout << lua_tostring(L, -1) << endl;
}