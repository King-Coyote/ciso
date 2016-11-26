#include "Event.hpp"

EventCreateGui::EventCreateGui(GuiObject* guiObj) {
	id = count;
	type = EventType::CREATE_GUI;
	m_guiObj = std::shared_ptr<GuiObject>(guiObj);
}

std::shared_ptr<GuiObject> EventCreateGui::getGuiObj() {
	return m_guiObj;
}