#pragma once

#include "MouseEventHandler.h"
#include "EventDispatcher.h"

template<typename TEventHandler>
using MouseEventDispatcherSpec = SpecializedEventDispatcher<TEventHandler, MouseEventHandler<TEventHandler>, MouseEvent, MouseContext>;

template<typename TEventHandler>
class MouseEventDispatcher
    :
    public MouseEventDispatcherSpec<TEventHandler>
{
public:
    MouseEventDispatcher(std::shared_ptr<MouseEventHandler<TEventHandler>> root)
        :
        MouseEventDispatcherSpec<TEventHandler>(root)
    {}
protected:
    virtual std::shared_ptr<MouseEventHandler<TEventHandler>> p_getNextEventHandler(const MouseEvent& e) const override
    {
        this->m_root->mouse(e);
        return this->m_root;
    }
};