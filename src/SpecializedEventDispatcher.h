#pragma once

#include "EventDispatcher.h"

template<typename TEventHandler, typename TSpecializedEventHandler, typename TEvent, typename TContext>
class SpecializedEventDispatcher
    :
    public EventDispatcher<TEventHandler>
{
public:
    SpecializedEventDispatcher(const SpecializedEventDispatcher&) = delete;

    virtual void setupContext(const BaseContext& ctx) override
    {
        return p_setupContext(static_cast<const TContext&>(ctx));
    }

protected:
    SpecializedEventDispatcher(std::shared_ptr<TSpecializedEventHandler> root)
        :
        m_root(root)
    {
    }

    virtual std::shared_ptr<TEventHandler> p_getNextEventHandler(const CoreEvent& e) const override
    {
        return std::static_pointer_cast<TEventHandler>(p_getNextEventHandler(static_cast<const TEvent&>(e)));
    }

    virtual bool p_canHandleEvent(const CoreEvent& e) const override
    {
        return dynamic_cast<const TEvent*>(&e);
    }

    virtual void p_setupContext(TContext ctx) {}
    virtual std::shared_ptr<TSpecializedEventHandler> p_getNextEventHandler(const TEvent& e) const = 0;

protected:
    std::shared_ptr<TSpecializedEventHandler> m_root;
};