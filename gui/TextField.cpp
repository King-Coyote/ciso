#include <cctype>
#include "TextField.hpp"
#include "GuiStyle.hpp"
#include "ResourceManager.hpp"
#include "EventQueue.hpp"

namespace ci {

TextField::TextField(
    mun::Table& t,
	mun::State& s,
    StyleMap& styleMap,
    ResourceManager& resourceManager
) :
    GuiObject(t, s, styleMap, resourceManager),
    text(sf::Text(
        sf::String(t.get<const char*>("string", "")),
        *resourceManager.getResource<sf::Font>(t.get<const char*>("font", "DejaVuSans.ttf")),
        t.get<int>("fontSize", 12)
    )),
    defaultString(t.get<const char*>("string", ""))
{
    mun::Table size = t.get<mun::Table>("size");
    this->panel.setSize(sf::Vector2f(size.get<double>(1), size.get<double>(2)));
    this->cursorSprite = sf::RectangleShape(sf::Vector2f(this->text.getCharacterSize()/24 + 1, this->panel.getSize().y - 2));
    this->cursorSprite.setFillColor(sf::Color::White);
    this->setPosition(this->localPosition);
    this->transitionToCurrentState();
}

void TextField::renderDrawables(float dt, sf::RenderTarget& window) {
    window.draw(this->panel);
    window.draw(this->text);
    if (this->cursorShown) {
        window.draw(this->cursorSprite);
    }
}

void TextField::updateDrawables(float dt) {
	if (this->state == GUISTATE_ACTIVE && this->cursorClock.getElapsedTime().asMilliseconds() >= 500) {
        this->cursorShown = !this->cursorShown;
		this->cursorClock.restart();
	}
}

void TextField::setDrawablesPosition(const sf::Vector2f& position) {
    this->panel.setPosition(position);
    this->text.setPosition(position);
}

sf::Vector2f TextField::getGlobalPos() {
    return this->panel.getPosition();
}

sf::Vector2f TextField::getLocalPos() {
    return this->localPosition;
}   

bool TextField::pointInBounds(float x, float y) {
    return this->panel.getGlobalBounds().contains(x, y);
}

void TextField::applyStyle(const GuiStyle& style) {
    this->panel.setFillColor(style.getBgColor());
    this->panel.setOutlineColor(style.getOutlineColor());
    this->panel.setOutlineThickness((float)style.getOutlineThickness());
}

void TextField::handleMouseReleaseEvent(EventInput* ei) {
    for (auto& child : this->children) {
        child->handleMouseReleaseEvent(ei);
    }
    if (!ei->isCaptured() && this->pointInBounds(ei->sfEvent.mouseButton.x, ei->sfEvent.mouseButton.y)) {
        ei->capture();
        switch (this->state) {
        case GUISTATE_CLICKED:
            this->state = GUISTATE_ACTIVE;
            // notify all listeners that this object hath been cliqq'd
            this->postEvent(new EventGuiButtonClicked(this->id));
            if (this->eventFunctors[HANDLERFUNC_CLICK]) {
                this->eventFunctors[HANDLERFUNC_CLICK]();
            }
            break;
        case GUISTATE_UNCLICKED:
            this->state = GUISTATE_ENABLED;
            break;
        case GUISTATE_ACTIVE:
            this->updateCursorPosition(this->getClickedCharIndex(sf::Vector2i(
                ei->sfEvent.mouseButton.x,
                ei->sfEvent.mouseButton.y
            )));
            break;
        }
    } else {
        if (this->state == GUISTATE_ACTIVE) {
            this->state = GUISTATE_ENABLED;
        }
    }
    this->transitionToCurrentState();
}

void TextField::handleTextEnteredEvent(EventInput* ei) {
    if (this->state != GUISTATE_ACTIVE) {
		return;
	}
    ei->capture();
    auto textEntered = ei->sfEvent.text.unicode;
	// handle backspace
	if (textEntered == '\b') {
		// set string to itself minus last character
        if (this->cursorIndex > 0) {
            std::string left = this->text.getString().substring(0, this->cursorIndex - 1);
            std::string right = this->text.getString().substring(this->cursorIndex, this->text.getString().getSize() - 1);
            this->text.setString(left + right);
            updateCursorPosition(this->cursorIndex - 1);
        }
	}
	// Handle return
	if (textEntered == '\r') {
		this->postEvent(new EventTextEntered(this->id, this->text.getString().toAnsiString()));
		this->text.setString("");
		updateCursorPosition(0);
		return;
	}
	const std::locale loc("");
	if (!std::isprint(static_cast<unsigned char>(textEntered))) {
		return;
	}
	// split string into bits
	if (this->cursorIndex == 0) {
		this->text.setString(textEntered + this->text.getString());
	} else if (this->cursorIndex == this->text.getString().getSize()) {
		this->text.setString(this->text.getString() + textEntered);
	} else {
		// cursor is somewhere in the middle of the string so you need to insert text by splitting string
		sf::String left = this->text.getString().substring(0, this->cursorIndex);
		sf::String right = this->text.getString().substring(this->cursorIndex, this->text.getString().getSize() - 1);
		this->text.setString(left + textEntered + right);
	}

	updateCursorPosition(this->cursorIndex + 1);
}

void TextField::handleKeyPressedEvent(EventInput* ei) {
	if (this->state != GUISTATE_ACTIVE) {
		return;
    }

    sf::Keyboard::Key keyPressed = ei->sfEvent.key.code;

	switch (keyPressed) {
	case sf::Keyboard::Left:
		if (this->cursorIndex > 0) {
			this->updateCursorPosition(this->cursorIndex - 1);
		}
		break;
	case sf::Keyboard::Right:
		if (this->cursorIndex < this->text.getString().getSize()) {
			this->updateCursorPosition(this->cursorIndex + 1);
		}
		break;
    case sf::Keyboard::Delete:
        if (this->cursorIndex < this->text.getString().getSize()) {
            std::string left = this->text.getString().substring(0, this->cursorIndex);
            std::string right = this->text.getString().substring(this->cursorIndex + 1, this->text.getString().getSize() + 1);
            this->text.setString(left + right);
            //updateCursorPosition(this->cursorIndex - 1);
        }
	}

}

void TextField::updateCursorPosition(unsigned int charIndex) {
	int bufferX = (int)(this->text.getCharacterSize()/24 + 2);
	int bufferY = 0;
	this->cursorIndex = charIndex;
	if (charIndex == 0) {
		// first char, set to position
		this->cursorSprite.setPosition(this->localPosition.x + bufferX, this->getGlobalPos().y + bufferY);
	} else if (charIndex >= this->text.getString().getSize()) {
		// index is the last char
		this->cursorSprite.setPosition(this->getGlobalPos().x + this->text.getGlobalBounds().width + bufferX, this->getGlobalPos().y + bufferY);
	} else {
		sf::Vector2f pos = this->text.findCharacterPos(charIndex);
		this->cursorSprite.setPosition(sf::Vector2f(pos.x - bufferX, pos.y - bufferY));
	}

	this->cursorClock.restart();
	this->cursorShown = true;
}

unsigned TextField::getClickedCharIndex(sf::Vector2i mousePos) {
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
					(this->getGlobalPos().x + this->text.getLocalBounds().width) - charPos.x,
					this->panel.getSize().y
				)
			);
		} else {
			// not last char, get rect based on consecutive char
			charRect = sf::Rect<float>(
				charPos,
				sf::Vector2f(
					this->text.findCharacterPos(index + 1).x - charPos.x,
					this->panel.getSize().y
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
				charRect.height
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

}