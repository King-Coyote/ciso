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

private:

	sf::RenderWindow& mainWindow;
	EventQueue& mainQ;
	Resources& m_resourceMgr;

	std::vector<std::shared_ptr<GuiObject>> m_guiObjs;

	std::unordered_map<std::string, std::shared_ptr<GuiStyle>> m_styleMap;

public:

	Gui(EventQueue& q, sf::RenderWindow& mainWindow, Resources& resourceMgr);

	void update(const float dt);
	void clear();
	void draw(const float dt);

	void handleEvent(std::shared_ptr<Event> e);

	void loadGuiObject(std::shared_ptr<GuiObject> obj);

	bool mainWindowIsOpen();

};