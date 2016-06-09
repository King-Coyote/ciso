
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Gui.hpp"

Gui::Gui(EventQueue* q) {

	this->mainQ = q;
	this->mainQ->registerHandler(this, EventType::INPUT); // replace with more general input event type
	this->mainWindow.create(sf::VideoMode(800, 600), "My window");
	this->mainWindow.setFramerateLimit(60);

}

void Gui::update(const float dt) {

	

}

void Gui::draw(const float dt) {



}

void Gui::handleEvent(const Event& e) {
	Event e2 = e;
	switch (e.type) {
	case EventType::INPUT:
	{
		EventInputMouseClick* eventMC = static_cast<EventInputMouseClick*>(&e2);
		if (eventMC == nullptr) { break; }
		
		break;
	}
	}
}

bool Gui::mainWindowIsOpen() {
	return this->mainWindow.isOpen();
}

sf::RenderWindow* Gui::getMainWin() {
	return &this->mainWindow;
}