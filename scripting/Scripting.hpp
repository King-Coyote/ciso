#pragma once

#include "luavm/State.hpp"
#include "EventQueue.hpp"
#include "EventHandler.hpp"
#include "EventSender.hpp"

namespace ci {

class Scripting : public EventHandler, public EventSender {
public:
    Scripting();
    ~Scripting();
    mun::State& getState();
protected:
    void onRunScript(EventRunScript* ers) override;
private:
    mun::State state;
};

}