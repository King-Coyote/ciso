#include "GuiTextField.hpp"

GuiTextField::GuiTextField(
	std::string id,
	sf::Vector2f position,
	sf::Vector2f spriteSize,
	EventQueue* eventQueue,
	int textSize,
	std::string defaultText
) {
	this->id = id;
	this->position = position;
	this->size = spriteSize;
}

void GuiTextField::onMouseEntered() {
	if (this->currentState == GUISTATE_ENABLED) {
		this->changeState(GUISTATE_HOVER);
	}
}

void GuiTextField::onMouseExited() {
	if (this->currentState == GUISTATE_HOVER || this->currentState == GUISTATE_CLICKED) {
		this->changeState(GUISTATE_ENABLED);
	}
}

void GuiTextField::onClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	if (this->currentState == GUISTATE_HOVER) {
		this->changeState(GUISTATE_CLICKED);
	}

}

void GuiTextField::onUnClick(sf::Vector2i mousePos, sf::Mouse::Button mouseButton) {

	if (this->currentState == GUISTATE_CLICKED) {
		this->changeState(GUISTATE_FOCUS);
		this->cursorClock.restart();
	} else {
		this->changeState(GUISTATE_ENABLED);
	}

}

void GuiTextField::draw(const float dt, sf::RenderWindow& win) {
	if (this->isHidden) { return; }

	win.draw(this->sprite);
	win.draw(this->text);
}

void GuiTextField::update(const float dt) {
	if (this->currentState == GUISTATE_FOCUS && this->cursorClock.getElapsedTime().asMilliseconds() >= 500) {
		blinkCursor();
		this->cursorClock.restart();
	}
}

void GuiTextField::blinkCursor() {
	if (this->cursorShown) {
		
	} else {

	}
}

void GuiTextField::createPolygon() {

	float radius = 3.0f;
	int smooth = 10;
	if (smooth <= 2) { return; }
	float pi = atan(1) * 4;
	float angleInc = (pi / 2.0f) / (smooth - 1);

	sf::Vector2f currStartPt = this->position;

	this->sprite = sf::ConvexShape(4 * smooth);

	this->sprite.setPointCount(smooth * 4);

	// top left corner
	currStartPt.x += radius;
	currStartPt.y += radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = angleInc * i;
		currPt.x -= radius * cos(currAngle);
		currPt.y -= radius * sin(currAngle);
		this->sprite.setPoint(i, currPt);
	}

	// top right corner
	currStartPt.x = (this->position.x + this->size.x) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi / 2.0f) - angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y -= radius * sin(currAngle);
		this->sprite.setPoint(i + smooth, currPt);
	}

	// bottom right corner
	currStartPt.y = (this->position.y + this->size.y) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		this->sprite.setPoint(i + (smooth * 2), currPt);
	}

	// bottom left corner
	currStartPt.x = (this->position.x + radius);
	currStartPt.y = (this->position.y + this->size.y) - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi / 2.0f) - angleInc * i;
		currPt.x -= radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		this->sprite.setPoint(i + (smooth * 3), currPt);
	}

	this->sprite.setOutlineThickness(2);
	this->sprite.setPosition(this->position);
}

void GuiTextField::initialiseVisualElements() {
	this->text = sf::Text(this->textString, *(this->guiStyle->getGuaranteedFont()), this->textSize);
	this->createPolygon();
}

void GuiTextField::changeToStateStyle(GuiState state) {

}