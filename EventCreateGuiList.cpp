#include "Event.hpp"

EventCreateGuiList::EventCreateGuiList(std::vector<GuiObject>* guiObjList) {

	m_guiObjList = std::shared_ptr<std::vector<GuiObject>>(guiObjList);

}

std::shared_ptr<std::vector<GuiObject>> EventCreateGuiList::getGuiObjList() {
	return m_guiObjList;
}