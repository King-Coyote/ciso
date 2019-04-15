#pragma once

#include "Event.hpp"
#include "EventQueue.hpp"

namespace ci {

class EventPostingKey;

class EventSender {
protected:
    void postEvent(Event* e) {
        EventQueue::postEvent({}, e);
    }
};

}