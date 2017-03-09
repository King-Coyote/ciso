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
#include "derp.hpp"

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
		"one", sf::Vector2f(100.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), "DEFAULT", 
		*mainQ,
		mainQ,
		"One"
	);

	//GuiObject* button2 = new GuiButton(
	//	"two", sf::Vector2f(215.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), "DEFAULT",
	//	mainQ,
	//	"Two"
	//);

	//GuiObject* text = new GuiText(
	//	"text1",
	//	sf::Vector2f(400, 400),
	//	"Fuk ye",
	//	"DEFAULT",
	//	20
	//);

	GuiObject* textField = new GuiTextField(
		"tf1",
		sf::Vector2f(100, 100),
		sf::Vector2f(200, 35),
		*mainQ,
		mainQ,
		"DEFAULT",
		30,
		""
	);

	mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(button1)));
	//mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(button2)));
	//mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(text)));
	mainQ->postEvent(std::shared_ptr<EventCreateGui>(new EventCreateGui(textField)));

	//sf::Font font = sf::Font();
	//font.loadFromFile("Assets\\default_font.ttf");
	//sf::Text textTest = sf::Text("fuk ya", font, 30);

	derp hurr = derp("fuk ya", *mainQ);
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