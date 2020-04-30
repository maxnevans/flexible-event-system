#pragma once

#include "Events.h"

class EventsHandler
{
public:
    virtual void handleEvent(const CoreEvent& e) const {}
    virtual void handleEvent(const InputEvent& e) const {}
    virtual void handleEvent(const KeyboardEvent& e) const {}
    virtual void handleEvent(const MouseEvent& e) const {}
    virtual void handleEvent(const MouseButtonEvent& e) const {}
    virtual void handleEvent(const MouseWheelEvent& e) const {}
};