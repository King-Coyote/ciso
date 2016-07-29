#include <iostream>
#include <string>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Gui.hpp"
#include "GuiButton.hpp"

sf::RenderWindow* Gui::mainWinStatic = nullptr;

Gui::Gui(EventQueue* q) {

	this->mainQ = q;
	this->mainQ->registerHandler(this, EventType::INPUT); // replace with more general input event type
	this->mainWindow.create(sf::VideoMode(800, 600), "CoyoteIso");
	this->mainWindow.setFramerateLimit(60);
	Gui::mainWinStatic = &this->mainWindow;

}

void Gui::update(const float dt) {

	

}

void Gui::draw(const float dt) {

	this->mainWindow.display();

}

void Gui::clear() {
	this->mainWindow.clear(sf::Color::Black);
}

void Gui::handleEvent(Event* e) {

	EventSfmlInput* eventSF= static_cast<EventSfmlInput*>(e);
	switch (eventSF->getSfmlType()) {
	case sf::Event::MouseEntered:

		break;
	}

}

bool Gui::mainWindowIsOpen() {
	return this->mainWindow.isOpen();
}

sf::RenderWindow* Gui::getMainWin() {
	return &this->mainWindow;
}

// STATIC GUI OBJECT FUNCTIONS
bool Gui::Button(float width, float height, float x, float y, std::string id) {
	//TODO: Desc

	//if (Gui::guiObjMap.count(id) > 0) {
	//	Gui::mainWinStatic->draw(guiObjMap[id]);
	//} else {
	//	//guiObjMap[id] = *(new GuiButton(width, height, x, y, id));
	//}

	//sf::RectangleShape rect(sf::Vector2f(width, height));
	//rect.setPosition(x, y);

	//Gui::mainWinStatic->draw(rect);

	return true;

}

void Gui::Text(std::string str, float x, float y, const sf::Font& font, unsigned int charSize) {
	//TODO: desc
	//TODO: change std::string to sf::String?

	sf::Text text;
	// TODO: get default font working
	text.setFont(font);
	text.setString(str);
	text.setPosition(sf::Vector2f(x, y));

	Gui::mainWinStatic->draw(text);

}