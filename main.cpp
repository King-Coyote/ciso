#include <vector>
#include <unordered_map>

#include "EventQueue.hpp"
#include "Event.hpp"
#include "Console.hpp"
#include "Gui.hpp"
#include "Input.hpp"
#include "Scene.hpp"

class derp {
	// dummy test class ya dingus

public:
	std::string str;
	derp(std::string str) : str(str) {};
	~derp() {
		std::cout << "Derp obj destroyed with string " << str << std::endl;
	}

};

int main() {

	EventQueue mainQ = EventQueue();
	sf::RenderWindow mainWindow;
	mainWindow.create(sf::VideoMode(800, 600), "CoyoteIso");
	mainWindow.setFramerateLimit(60);

	Console console = Console(mainQ);
	Gui gui = Gui(mainQ, mainWindow);
	Input input = Input(mainQ, mainWindow);

	Scene scene = Scene();

	sf::Clock clock;
	sf::Time elapsed;
	float dt = 0.0f;

	derp* durr = new derp("hurrdurr");

	while (gui.mainWindowIsOpen()) {
		elapsed = clock.restart();
		dt = elapsed.asSeconds();
		mainQ.processEvents();
		gui.clear();
		scene.update(dt);
		scene.draw(dt);
		input.update(dt);
		gui.update(dt);
		gui.draw(dt);
	}
}