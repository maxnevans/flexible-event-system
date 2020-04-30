#pragma once

#include "Hierarchal.h"
#include "EventsHandler.h"

template<typename TNode>
class MouseEventHandler
    :
    public virtual Hierarchal<TNode>,
    public virtual EventsHandler
{
public:
    virtual void mouse(const MouseEvent& e) = 0;
};