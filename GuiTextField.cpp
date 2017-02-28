#include "GuiTextField.hpp"

//DELETEME
#include <iostream>

GuiTextField::GuiTextField(
	std::string id,
	sf::Vector2f position,
	sf::Vector2f spriteSize,
	EventQueue* eventQueue,
	std::string styleId,
	int textSize,
	std::string defaultString
) {
	this->id = id;
	this->position = position;
	this->size = spriteSize;
	this->eventQueue = eventQueue;
	this->styleId = styleId;
	this->defaultString = defaultString;
	this->textSize = textSize;

	this->eventQueue->registerHandler(this, EventType::INPUT);
}

void GuiTextField::setPos(sf::Vector2f newPos) {
	this->position = newPos;
	this->text.setPosition(newPos);
	this->sprite.setPosition(newPos);
	updateCursorPosition(this->cursorPosition);
}

//TODO: create settextposition method which puts the text in the right place

bool GuiTextField::pointInsideBounds(sf::Vector2i point) {
	return (this->sprite.getGlobalBounds().contains(point.x, point.y));
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
		return;
	}

	if (this->currentState == GUISTATE_FOCUS) {
		// if not clicked inside, unfocus and stop drawing cursor
		if (!pointInsideBounds(mousePos)) {
			this->changeState(GUISTATE_ENABLED);
			this->cursorShown = false;
		} else { // if inside and focused, re-establish position of cursor
			updateCursorPosition(getClickedCharIndex(mousePos));
		}
	}

}

void GuiTextField::handleEvent(std::shared_ptr<Event> e) {
	switch (e->type) {
	case EventType::INPUT: {
		std::shared_ptr<EventSfmlInput> eventSF = std::static_pointer_cast<EventSfmlInput>(e);
		switch (eventSF->getEventPtr()->type) {
		case sf::Event::TextEntered: {
			onTextEntered(eventSF->getEventPtr()->text.unicode);
		}
		}
	}
	}
}

void GuiTextField::onTextEntered(sf::String textEntered) {
	if (this->currentState != GUISTATE_FOCUS) {
		return;
	}
	// handle backspace
	if (textEntered == '\b') {
		// set string to itself minus last character
		deleteTextAtIndex(this->cursorPosition);
		return;
	}
	// Handle return
	if (textEntered == '\r') {
		sendEnteredText();
		this->text.setString("");
		updateCursorPosition(0);
		return;
	}
	this->text.setString(this->text.getString() + textEntered);
	updateCursorPosition(this->text.getString().getSize());
}

void GuiTextField::deleteTextAtIndex(int index) {
	if (index == 0)
		return;

	std::string left = this->text.getString().substring(0, index - 1);
	std::string right = this->text.getString().substring(index, this->text.getString().getSize() - 1);
	this->text.setString(left + right);
	updateCursorPosition(index - 1);
}

void GuiTextField::sendEnteredText() {
	std::shared_ptr<EventGuiTextEntered> eventPtr(new EventGuiTextEntered(this->id, this->text.getString()));
	this->eventQueue->postEvent(eventPtr);
}

void GuiTextField::draw(const float dt, sf::RenderWindow& win) {
	if (this->isHidden) { return; }

	win.draw(this->sprite);
	win.draw(this->text);
	if (this->cursorShown) {
		win.draw(this->cursorSprite);
	}
}

void GuiTextField::update(const float dt) {
	if (this->currentState == GUISTATE_FOCUS && this->cursorClock.getElapsedTime().asMilliseconds() >= 500) {
		blinkCursor();
		this->cursorClock.restart();
	}
}

void GuiTextField::blinkCursor() {
	if (this->cursorShown) {
		this->cursorShown = false;
	} else {
		this->cursorShown = true;
	}
}

void GuiTextField::updateCursorPosition(unsigned int charIndex) {
	int buffer = 1;
	this->cursorPosition = charIndex;
	if (charIndex == 0) {
		// first char, set to position
		this->cursorSprite.setPosition(this->position.x + buffer, this->position.y + buffer);
	} else if (charIndex >= this->text.getString().getSize()) {
		// index is the last char
		this->cursorSprite.setPosition(this->position.x + this->text.getGlobalBounds().width + buffer, this->position.y + buffer);
	} else {
		sf::Vector2f pos = this->text.findCharacterPos(charIndex);
		this->cursorSprite.setPosition(sf::Vector2f(pos.x - buffer, pos.y - buffer));
	}
}

int GuiTextField::getClickedCharIndex(sf::Vector2i mousePos) {

	sf::Vector2f charPos;
	sf::Rect<float> charRect;
	sf::Vector2f nextPos; // this is the position of the next char, or the end of the line
	unsigned int index;
	for (index = 0; index < this->text.getString().getSize(); index++) {

		charPos = this->text.findCharacterPos(index);
		if (index == this->text.getString().getSize() - 1) {
			// last char, need to get rect based on bounds, not next char
			nextPos = sf::Vector2f(
				(this->position.x + this->text.getLocalBounds().width),
				(this->position.y + this->text.getLocalBounds().height)
			);
			charRect = sf::Rect<float>(
				charPos,
				sf::Vector2f(
					nextPos.x - charPos.x,
					this->size.y
				)
			);
		} else {
			// not last char, get rect based on consecutive char
			nextPos = this->text.findCharacterPos(index + 1);
			charRect = sf::Rect<float>(
				charPos,
				sf::Vector2f(
					nextPos.x - charPos.x,
					this->size.y
				)
			);
		}

		// use the rect found in the if statement above to see if the mouse is in the char
		if (charRect.contains(static_cast<sf::Vector2f>(mousePos))) {
			sf::Rect<float> charLeftHalf = sf::Rect<float>(
				charRect.left, 
				charRect.top,
				charRect.width / 2.0f, 
				charRect.height
				);
			sf::Rect<float> charRightHalf = sf::Rect<float>(
				charRect.left + charRect.width / 2.0f,
				charRect.top,
				charRect.width / 2.0f,
				charRect.top
				);
			if (charLeftHalf.contains(static_cast<sf::Vector2f>(mousePos))) {
				return index;
			}
			if (charRightHalf.contains(static_cast<sf::Vector2f>(mousePos))) {
				return index + 1;
			}
		}

	}
	// no char matched, so it should just be at the end of the string.
	return index;
}

void GuiTextField::createPolygon() {

	float radius = 1.5f;
	int smooth = 10;
	if (smooth <= 2) { return; }
	float pi = atan(1) * 4;
	float angleInc = (pi / 2.0f) / (smooth - 1);

	sf::Vector2f currStartPt = sf::Vector2f(0, 0);

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
	currStartPt.x = this->size.x - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi / 2.0f) - angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y -= radius * sin(currAngle);
		this->sprite.setPoint(i + smooth, currPt);
	}

	// bottom right corner
	currStartPt.y = this->size.y - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = angleInc * i;
		currPt.x += radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		this->sprite.setPoint(i + (smooth * 2), currPt);
	}

	// bottom left corner
	currStartPt.x = radius;
	currStartPt.y = this->size.y - radius;
	for (int i = 0; i < smooth; i++) {
		sf::Vector2f currPt = currStartPt;
		float currAngle = (pi / 2.0f) - angleInc * i;
		currPt.x -= radius * cos(currAngle);
		currPt.y += radius * sin(currAngle);
		this->sprite.setPoint(i + (smooth * 3), currPt);
	}

	this->sprite.setOutlineThickness(2);
	//this->sprite.setPosition(this->position);
}

void GuiTextField::initialiseVisualElements() {
	this->text = sf::Text(this->defaultString, sf::Font(), this->textSize);
	this->cursorSprite = sf::RectangleShape(sf::Vector2f(1, this->size.y - 2));
	// TODO: DEFAULTIST TRASH, replace with color from textcolor from the guistyle
	this->cursorSprite.setFillColor(sf::Color::White);
	createPolygon();
	this->changeState(GUISTATE_ENABLED);
	this->setPos(this->position);
	updateCursorPosition(0);
}

void GuiTextField::changeToStateStyle(GuiState state) {
	if (this->guiStyle == nullptr) {
		return;
	}

	if (this->guiStyle->getBgColor(state) != nullptr) {
		this->sprite.setFillColor(*(this->guiStyle->getBgColor(state)));
	}
	if (this->guiStyle->getOutlineColor(state) != nullptr) {
		this->sprite.setOutlineColor(*(this->guiStyle->getOutlineColor(state)));
	}
	if (this->guiStyle->getStateFont(state) != nullptr) {
		this->text.setFont(*(this->guiStyle->getStateFont(state)));
	}
}