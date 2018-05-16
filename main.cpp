#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>

#include "EventQueue.hpp"
#include "Event.hpp"
#include "Console.hpp"
#include "Gui.hpp"
#include "Input.hpp"
#include "Scene.hpp"
#include "Resources.hpp"

using namespace std;

int main() {

	sf::RenderWindow mainWindow;
	mainWindow.create(sf::VideoMode(800, 600), "CoyoteIso");
	mainWindow.setFramerateLimit(60);

	unique_ptr<EventQueue> mainQ = unique_ptr<EventQueue>(new EventQueue());

	unique_ptr<Input> input = unique_ptr<Input>(new Input(*mainQ, mainWindow));
	unique_ptr<Gui> gui = unique_ptr<Gui>(new Gui(mainWindow));

	sf::Clock clock;
	sf::Time elapsed;
	float dt = 0.0f;

	while (mainWindow.isOpen()) {
		elapsed = clock.restart();
		dt = elapsed.asSeconds();
		input->update(dt);
		mainQ->processEvents();
		gui->clear();
		gui->update(dt);
		gui->draw(dt);
	}
}