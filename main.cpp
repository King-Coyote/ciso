#include <vector>
#include <unordered_map>

#include "EventQueue.hpp"
#include "Event.hpp"
#include "Console.hpp"
#include "Gui.hpp"
#include "Input.hpp"
#include "Scene.hpp"
#include "GuiButton.hpp"

class derp {
	// dummy test class ya dingus
	// fyerhealth

public:
	std::string str;
	derp(std::string str) : str(str) {};
	~derp() {
		std::cout << "Derp obj destroyed with string " << str << std::endl;
	}

};

int main() {

	EventQueue* mainQ = new EventQueue();
	sf::RenderWindow mainWindow;
	mainWindow.create(sf::VideoMode(800, 600), "CoyoteIso");
	mainWindow.setFramerateLimit(60);

	Console* console = new Console(*mainQ);
	Gui* gui = new Gui(*mainQ, mainWindow);
	//std::cout << "Size of gui system is " << sizeof(gui) << std::endl;
	Input* input = new Input(*mainQ, mainWindow);

	GuiObject* button1 = new GuiButton("one", sf::Vector2f(100.0f, 50.0f), sf::Vector2f(100.0f, 100.0f), "none", "dooP");

	mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(button1)));

	Scene scene = Scene();

	sf::Clock clock;
	sf::Time elapsed;
	float dt = 0.0f;

	while (gui->mainWindowIsOpen()) {
		elapsed = clock.restart();
		dt = elapsed.asSeconds();
		mainQ->processEvents();
		gui->clear();
		scene.update(dt);
		scene.draw(dt);
		input->update(dt);
		gui->update(dt);
		gui->draw(dt);
	}
}