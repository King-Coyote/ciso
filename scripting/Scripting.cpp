#include "Scripting.hpp"
#include <iostream>

namespace ci {

Scripting::Scripting() :
    EventHandler({EventType::RUNSCRIPT})
{
    this->state.openLibs();
}

Scripting::~Scripting() {}

mun::State& Scripting::getState() {
    return this->state;
}

// EVENT HANDLING
void Scripting::onRunScript(EventRunScript* ers) {
    this->state.runScript(ers->filename);
}

}