#include <cmath>

#include "GuiAreaGrid.hpp"

void GuiAreaGrid::setPos(sf::Vector2f newPos) {

	

}

void GuiAreaGrid::addObj(GuiObject* obj, int row, int col) {



}

void GuiAreaGrid::addObj(std::shared_ptr<GuiObject> obj, int row, int col) {

	m_numCols = (int)fmax(m_numCols, col);
	m_numRows = (int)fmax(m_numRows, row);

	void rearrangeObjects();

}

void GuiAreaGrid::rearrangeObjects() {

	for (auto obj : m_guiObjs) {

	}

}

