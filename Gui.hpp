#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "EventHandler.hpp"
#include "EventQueue.hpp"
#include "GuiObject.hpp"
#include "Resources.hpp"
#include "GuiStyle.hpp"

class Gui : public EventHandler {

public: // METHODS

	Gui(EventQueue& q, sf::RenderWindow& mainWindow, Resources& resourceMgr);

	void update(const float dt);
	void clear();
	void draw(const float dt);

	void loadGuiObject(std::shared_ptr<GuiObject> obj);

	bool mainWindowIsOpen();

protected: // METHODS
	
	//EVENTS
	void onCreateGui(std::shared_ptr<GuiObject> guiObj);

private: // MEMBERS

	sf::RenderWindow& mainWindow;
	Resources& resourceMgr;

	std::vector<std::shared_ptr<GuiObject>> guiObjs;

	std::unordered_map<std::string, std::shared_ptr<GuiStyle>> m_styleMap;

};