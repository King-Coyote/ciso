#include "GuiWidget.hpp"


bool GuiWidget::hide() {
	if (this->isVisible) {
		this->isVisible = false;
		return true;
	} else {
		return false;
	}
}

bool GuiWidget::show() {
	if (!this->isVisible) {
		this->isVisible = true;
		return true;
	} else {
		return false;
	}
}