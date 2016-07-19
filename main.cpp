
#include "EventQueue.hpp"
#include "Event.hpp"
#include "Console.hpp"
#include "Gui.hpp"
#include "Input.hpp"
#include "Scene.hpp"

int main() {

	EventQueue* mainQ = new EventQueue();

	Console* console = new Console(mainQ);
	Gui* gui = new Gui(mainQ);
	Input* input = new Input(mainQ, gui->getMainWin());

	Scene* scene = new Scene();

	sf::Clock clock;
	sf::Time elapsed;
	float dt = 0.0f;

	while (gui->mainWindowIsOpen()) {
		elapsed = clock.restart();
		dt = elapsed.asSeconds();
		mainQ->processEvents();
		gui->clear();
		scene->update(dt);
		input->update(dt);
		gui->update(dt);
		gui->draw(dt);
	}
	
	return 0;

}