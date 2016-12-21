#include <vector>
#include <unordered_map>
#include <iostream>

#include "EventQueue.hpp"
#include "Event.hpp"
#include "Console.hpp"
#include "Gui.hpp"
#include "Input.hpp"
#include "Scene.hpp"
#include "GuiButton.hpp"
#include "GuiArea.hpp"

class derp : public EventHandler {
	// dummy test class ya dingus
	// fyerhealth

public:
	std::string str;
	derp(std::string str) : str(str) {
	
	};
	void derpFunction(bool isItTrue) {
		std::cout << "derp with id " << str << "fired!\n";
	}
	void invoke() {
		derpFunction(true);
	}
	void handleEvent(std::shared_ptr<Event> e) {
		switch (e->type) {
		case EventType::GUI_BUTTONCLICKED: {
			std::shared_ptr<EventGuiButtonClicked> egbc = std::static_pointer_cast<EventGuiButtonClicked>(e);
			std::cout << "Event fired with butt id " << egbc->getId() << "\n";
		}
		default: {

		}
		}
	}
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

	GuiObject* button1 = new GuiButton(
		"one", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 100.0f), "none", "dooP",
		mainQ
	);
	GuiObject* button2 = new GuiButton(
		"two", sf::Vector2f(100.0f, 0.0f), sf::Vector2f(100.0f, 100.0f), "none", "dooP",
		mainQ
	);
	GuiObject* button3 = new GuiButton(
		"three", sf::Vector2f(0.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), "none", "dooP",
		mainQ
	);

	GuiObject* button4 = new GuiButton(
		"four", sf::Vector2f(300.0f, 300.0f), sf::Vector2f(75.0f, 75.0f), "none", "dooP",
		mainQ
	);

	GuiArea* area = new GuiArea("area", sf::Vector2f(100.0f, 100.0f), sf::Vector2f(300.0f, 300.0f));
	area->addObj(button1);
	area->addObj(button2);
	area->addObj(button3);

	mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(area)));
	mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(button4)));
	derp hurr = derp("fuk ya");
	mainQ->registerHandler(&hurr, EventType::GUI_BUTTONCLICKED);
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