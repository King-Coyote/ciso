
#include "EventHandlerInput.hpp"
#include "EventQueue.hpp"
#include "Event.hpp"
#include "Console.hpp"

int main() {

	Console* console = new Console();
	EventQueue* q = new EventQueue(2048);

	q->registerHandler(console, EventType::DEBUG);

	while (true) {
	}
	
	return 0;

}