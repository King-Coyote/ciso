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
#include "Resources.hpp"
#include "GuiText.hpp"
#include "GuiTextField.hpp"

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
			break;
		}
		case EventType::GUI_TEXTENTERED: {
			std::shared_ptr<EventGuiTextEntered> egte = std::static_pointer_cast<EventGuiTextEntered>(e);
			std::cout << "TE Event fired with field id " << egte->getId() << " and text entered was:\n" << egte->getTextEntered().toAnsiString() << "\n";
			break;
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
	Resources* resources = new Resources();
	sf::RenderWindow mainWindow;
	mainWindow.create(sf::VideoMode(800, 600), "CoyoteIso");
	mainWindow.setFramerateLimit(60);

	Console* console = new Console(*mainQ);
	Gui* gui = new Gui(*mainQ, mainWindow, *resources);
	Input* input = new Input(*mainQ, mainWindow);

	GuiObject* button1 = new GuiButton(
		"one", sf::Vector2f(100.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), "DEFAULT", "One",
		mainQ
	);

	GuiObject* button2 = new GuiButton(
		"two", sf::Vector2f(215.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), "DEFAULT", "Two",
		mainQ
	);

	GuiObject* text = new GuiText(
		"text1",
		sf::Vector2f(400, 400),
		"Fuk ye",
		"DEFAULT",
		20
	);

	GuiObject* textField = new GuiTextField(
		"tf1",
		sf::Vector2f(100, 100),
		sf::Vector2f(200, 35),
		mainQ,
		"DEFAULT",
		30,
		""
	);

	mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(button1)));
	mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(button2)));
	mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(text)));
	mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(textField)));

	//sf::Font font = sf::Font();
	//font.loadFromFile("Assets\\default_font.ttf");
	//sf::Text textTest = sf::Text("fuk ya", font, 30);

	derp hurr = derp("fuk ya");
	mainQ->registerHandler(&hurr, EventType::GUI_BUTTONCLICKED);
	mainQ->registerHandler(&hurr, EventType::GUI_TEXTENTERED);
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