#pragma once

#include "SpecializedEventDispatcher.h"
#include "KeyboardEventHandler.h"

template<typename TEventHandler>
using KeyboardEventDispatcherSpec = SpecializedEventDispatcher<TEventHandler, KeyboardEventHandler<TEventHandler>, KeyboardEvent, KeyboardContext>;

template<typename TEventHandler>
class KeyboardEventDispatcher
    :
    public KeyboardEventDispatcherSpec<TEventHandler>
{
public:
    KeyboardEventDispatcher(std::shared_ptr<KeyboardEventHandler<TEventHandler>> root)
        :
        KeyboardEventDispatcherSpec<TEventHandler>(root)
    {
    }

protected:
    virtual std::shared_ptr<typename KeyboardEventHandler<typename TEventHandler>> p_getNextEventHandler(const KeyboardEvent& e) const override
    {
        this->m_root->key(e);
        return this->m_root;
    }

    virtual void p_setupContext(KeyboardContext ctx)
    {
        m_focusedComponent = ctx.focusedComponent;
    }

private:
    int m_focusedComponent = 0;
};