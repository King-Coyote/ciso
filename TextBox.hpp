#pragma once

// DELETEME
#include <stdio.h>
#include "EventHandler.hpp"
#include "EventQueue.hpp"

#include "Resources.hpp"
#include "GuiObject.hpp"
#include "SFML\Graphics.hpp"

class TextBox : public GuiObject, public EventHandler {

public:

	TextBox(EventQueue& q) :
		GuiObject("tb", sf::Vector2f(100.0f, 100.0f), sf::Vector2f(150.0f, 150.0f), "DEFAULT"),
		EventHandler(q, {EventType::INPUT})
	{}

	void draw(const float dt, sf::RenderWindow& win) {
		sf::View def = win.getDefaultView();
		win.setView(this->view);
		win.draw(this->text);
		win.setView(def);
	}

	void update(const float dt) {}
	
private:

	sf::Text text;
	sf::View view;
	sf::FloatRect clippingRect;
	float zoomFactor = 1.05f;

	void initialiseVisualElements() {
		clippingRect = sf::FloatRect(this->position.x / 1280.0f, this->position.y / 720.0f, this->size.x / 1280.0f, this->size.y / 720.0f);
		this->view.reset(sf::FloatRect(this->position.x+(this->size.x/2.0f), this->position.y+(this->size.y/2.0f), this->size.x, this->size.y));
		this->text = sf::Text("Test test\ntest\nTest test test\nTest test test test test test", sf::Font(), 30);
		this->text.setPosition(this->position);
		this->text.setColor(sf::Color::White);
		this->changeState(GUISTATE_ENABLED);
		float xPrint = (this->position.x / 1280.0f);
		float yPrint = (this->position.y / 720.0f);		
		//this->view.move(-510, -510);
		//view.setSize(this->size);
		view.setViewport(clippingRect);
	}

	void onKeyPressed(sf::Keyboard::Key keyCode) {
		if (keyCode == sf::Keyboard::Z) {
			this->view.zoom(zoomFactor);
			std::printf("%.4f, %.4f\n", this->view.getSize().x, this->view.getSize().y);
		} else if (keyCode == sf::Keyboard::Right) {
			this->view.move(-10.0f, 0.0f);
		} else if (keyCode == sf::Keyboard::Left) {
			this->view.move(10.0f, 0.0f);
		}
	}

	void changeToStateStyle(GuiState state) {
		if (this->guiStyle == nullptr) {
			return;
		}

		if (this->guiStyle->getStateFont(state) != nullptr) {
			this->text.setFont(*(this->guiStyle->getStateFont(state)));
		}
	}

};
