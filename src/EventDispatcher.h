#pragma once

#include <memory>

#include "Events.h"
#include "EventDispatcherContexts.h"

template<typename TEventHandler>
class EventDispatcher
{
public:
    template<typename TEvent>
    bool dispatch(TEvent e)
    {
        auto handler = p_getNextEventHandler(e);
        handler->handleEvent(e);

        return false;
    }
    bool canHandleEvent(const CoreEvent& e) const
    {
        return p_canHandleEvent(e);
    }

    virtual void setupContext(const BaseContext& ctx) = 0;

protected:
    virtual std::shared_ptr<TEventHandler> p_getNextEventHandler(const CoreEvent&) const = 0;
    virtual bool p_canHandleEvent(const CoreEvent& e) const = 0;
};