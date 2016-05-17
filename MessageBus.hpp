#pragma once

#include <stack>
#include <vector>

#include "MessageHandler.hpp"

template<typename T>
class MessageBus {

private:

	template<typename T2>
	std::vector<MessageHandler<T2>*> handlers;
	std::stack<Message> messages;

public:

	//void send(Message* message);

	void dispatchMessages();

};

/*

Need a messaging system where:

- objects that inherit from interface/virtual class MessageListener can hook themselves up to the messageBus to receive messages of a specific type.
Once they are hooked in, they are given messages by the bus (what does that mean?) and act on it.

so a listener class needs:
RegisterForMessages(messageBus*, messageType),
DeRegister(messageBus*),

ANd then the messageBus needs to have a collection of listeners for each type of event?...e


*/