#pragma once

#include "Hierarchal.h"
#include "EventsHandler.h"

template<typename TNode>
class KeyboardEventHandler
    :
    public virtual Hierarchal<TNode>,
    public virtual EventsHandler
{
public:
    virtual void key(const KeyboardEvent& e) = 0;
};