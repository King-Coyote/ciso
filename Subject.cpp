#include "Subject.hpp"

void Subject::addObserver(Observer* observer) {

	observer->next = head;
	head = observer;

}

void Subject::removeObserver(Observer* observer) {

	// handle case of removing the observer at the start of the daisychain/linked list
	if (head == observer) {
		head = observer->next;
		observer->next = nullptr;
	}

	Observer* current = head;
	while (current != nullptr) {
		if (current->next == observer) {
			current->next = observer->next;
			observer->next = nullptr;
			return;
		}

		current = current->next;
	}

}

void Subject::notifyObservers(Event* e) {

	Observer* current = head;
	while (current != nullptr) {
		current->onNotify(e);
		current = current->next;
	}

}