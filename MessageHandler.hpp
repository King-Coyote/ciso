#pragma once

#include "MessageBus.hpp"

template<typename T>
class MessageHandler {

private:

	MessageBus* messageBus;

public:

	virtual void handleMessage(T* message) = 0;
};