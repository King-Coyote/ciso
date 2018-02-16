#include "GuiTextField.hpp"
#include "GuiObject.hpp"
#include "GuiStyle.hpp"
#include "EventQueue.hpp"

//DELETEME
#include <iostream>
#include <math.h>

GuiTextField::GuiTextField(
	std::string id,
	sf::Vector2f position,
	sf::Vector2f spriteSize,
	EventQueue& incomingEventQueue,
	EventQueue* outgoingEventQueue,
	std::string styleId,
	int textSize,
	std::string defaultString
) :
	GuiObject(id, position, spriteSize, styleId),
	EventHandler(incomingEventQueue, {EventType::INPUT}),
	defaultString(defaultString),
	textSize(textSize),
	incomingEventQueue(incomingEventQueue),
	outgoingEventQueue(outgoingEventQueue)
{}

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

//TODO make these only respond to left clicks or what have you
void GuiTextField::onMouseButtonPressed(sf::Vector2i mousePos, sf::Mouse::Button button) {

	if (this->currentState == GUISTATE_HOVER) {
		this->changeState(GUISTATE_CLICKED);
	}

}

void GuiTextField::onMouseButtonReleased(sf::Vector2i mousePos, sf::Mouse::Button button) {

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

void GuiTextField::onKeyPressed(sf::Keyboard::Key keyPressed) {
	if (this->currentState != GUISTATE_FOCUS)
		return;

	switch (keyPressed) {
	case sf::Keyboard::Left:
		if (this->cursorPosition > 0) {
			this->updateCursorPosition(this->cursorPosition - 1);
		}
		break;
	case sf::Keyboard::Right:
		if (this->cursorPosition < this->text.getString().getSize()) {
			this->updateCursorPosition(this->cursorPosition + 1);
		}
		break;
	}

}

void GuiTextField::onTextEntered(sf::Uint32 textEntered) {
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
	const std::locale loc("");
	if (!std::isprint(textEntered, loc)) {
		return;
	}

	// split string into bits
	if (this->cursorPosition == 0) {
		this->text.setString(textEntered + this->text.getString());
	} else if (this->cursorPosition == this->text.getString().getSize()) {
		this->text.setString(this->text.getString() + textEntered);
	} else {
		// cursor is somewhere in the middle of the string so you need to insert text by splitting string
		sf::String left = this->text.getString().substring(0, this->cursorPosition);
		sf::String right = this->text.getString().substring(this->cursorPosition, this->text.getString().getSize() - 1);
		this->text.setString(left + textEntered + right);
	}

	updateCursorPosition(this->cursorPosition + 1);

}

void GuiTextField::deleteTextAtIndex(int index) {
	if (index <= 0)
		return;

	std::string left = this->text.getString().substring(0, index - 1);
	std::string right = this->text.getString().substring(index, this->text.getString().getSize() - 1);
	this->text.setString(left + right);
	updateCursorPosition(index - 1);
}

void GuiTextField::sendEnteredText() {
	std::shared_ptr<EventGuiTextEntered> eventPtr(new EventGuiTextEntered(this->id, this->text.getString()));
	this->outgoingEventQueue->postEvent(eventPtr);
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
	int bufferX = 4;
	int bufferY = 2;
	this->cursorPosition = charIndex;
	if (charIndex == 0) {
		// first char, set to position
		this->cursorSprite.setPosition(this->position.x + bufferX, this->position.y + bufferY);
	} else if (charIndex >= this->text.getString().getSize()) {
		// index is the last char
		this->cursorSprite.setPosition(this->position.x + this->text.getGlobalBounds().width + bufferX, this->position.y + bufferY);
	} else {
		sf::Vector2f pos = this->text.findCharacterPos(charIndex);
		this->cursorSprite.setPosition(sf::Vector2f(pos.x - bufferX, pos.y - bufferY));
	}

	this->cursorClock.restart();
	this->cursorShown = true;
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
			charRect = sf::Rect<float>(
				charPos,
				sf::Vector2f(
					(this->position.x + this->text.getLocalBounds().width) - charPos.x,
					this->size.y
				)
			);
		} else {
			// not last char, get rect based on consecutive char
			charRect = sf::Rect<float>(
				charPos,
				sf::Vector2f(
					this->text.findCharacterPos(index + 1).x - charPos.x,
					this->size.y
				)
			);
		}

		// use the rect found in the if statement above to see if the mouse is in the char.
		// the rect is split into two halves to give the user better control
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
	this->cursorShown = false;
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