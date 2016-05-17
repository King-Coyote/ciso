#pragma once

#include "MessageBus.hpp"

class Listener {

private:

	MessageBus* messageBus;

public:

	virtual void Register(MessageBus* bus) = 0;

	virtual void Deregister() = 0;

};