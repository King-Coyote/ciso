#pragma once

#include "GuiArea.hpp"

class GuiAreaGrid : public GuiObject {
	
private:

	struct GridObj {
		unsigned int row;
		unsigned int col;
		std::shared_ptr<GuiObject> ptr;
	};

	int m_numCols;
	int m_numRows;

	float m_xPad;
	float m_yPad;

	std::vector<GridObj> m_guiObjs;

public:

	GuiAreaGrid(std::string id, sf::Vector2f position, sf::Vector2f size);
	GuiAreaGrid(std::string id, sf::Vector2f position, sf::Vector2f size, std::vector<std::shared_ptr<GuiObject>> objs);
	GuiAreaGrid(std::string id, sf::Vector2f position, sf::Vector2f size, std::vector<GuiObject*> objs);

	void addObj(GuiObject* obj, int row, int col);
	void addObj(std::shared_ptr<GuiObject> obj, int row, int col);

	void rearrangeObjects();

	void setPos(sf::Vector2f newPos);


};