#include <iostream>
#include <string>

#include "GenericSystem.hpp"

void GenericSystem::onNotify(Event* e) {

	std::cout << "I HAVE BEEN NOTIFIED AND MY NAME IS " + name + "\n";
	switch (e->type) {

		case EventType::INPUT:
			InputEvent* iEvent = (InputEvent*)e;
			std::cout << "X is " << std::to_string(iEvent->mouseX) << ", Y is " << std::to_string(iEvent->mouseY) << ", and type is INPUT";

	}

}