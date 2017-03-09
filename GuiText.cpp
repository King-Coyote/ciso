#include "GuiText.hpp"

GuiText::GuiText(
	std::string id,
	sf::Vector2f position,
	sf::Vector2f size,
	std::string styleId,
	std::string text,
	int textSize
) :
	GuiObject(id, position, size, styleId),
	textString(textString),
	textSize(textSize)
{
	// TODO does changestate need to be in the constructor?
	this->changeState(GUISTATE_ENABLED);
}

std::string GuiText::setText(std::string newString) {
	std::string lastString = this->text.getString();
	this->text.setString(newString);
	return lastString;
}

// OVERRIDES
void GuiText::setPos(sf::Vector2f newPos) {
	this->position = newPos;
	this->text.setPosition(newPos);
}

void GuiText::setSize(sf::Vector2f newSize) {
}

void GuiText::draw(const float dt, sf::RenderWindow& win) {
	if (this->isHidden) { return; }

	win.draw(this->text);
}

void GuiText::update(const float dt) {

}

void GuiText::initialiseVisualElements() {
	this->text = sf::Text(this->textString, *(this->guiStyle->getGuaranteedFont()), this->textSize);
	this->text.setPosition(this->position);
}

void GuiText::changeToStateStyle(GuiState state) {
	if (this->guiStyle == nullptr) {
		return;
	}

	if (this->guiStyle->getStateFont(state) != nullptr) {
		this->text.setFont(*(this->guiStyle->getStateFont(state)));
	}
	if (this->guiStyle->getTextColor(state) != nullptr) {
		this->text.setColor(*(this->guiStyle->getTextColor(state)));
	}
}