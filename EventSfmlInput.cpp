#include "Event.hpp"

EventSfmlInput::EventSfmlInput(sf::Event sfe) {
	type = EventType::INPUT;
	sfEvent = sfe;
}

sf::Event* EventSfmlInput::getEventPtr() {
	return &(this->sfEvent);
}