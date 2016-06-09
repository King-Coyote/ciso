
#include "EventQueue.hpp"
#include "Event.hpp"
#include "Console.hpp"
#include "Gui.hpp"
#include "Input.hpp"

int main() {

	EventQueue* mainQ = new EventQueue();

	Console* console = new Console(mainQ);
	Gui* gui = new Gui(mainQ);
	Input* input = new Input(mainQ, gui->getMainWin());

	
	sf::Clock clock;
	sf::Time elapsed;
	float dt = 0.0f;

	while (gui->mainWindowIsOpen()) {
		elapsed = clock.restart();
		dt = elapsed.asSeconds();
		gui->update(dt);
		input->update(dt);
		mainQ->processEvents();
	}
	
	return 0;

}