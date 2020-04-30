#pragma once

#include "EventDispatcher.h"
#include <vector>
#include <unordered_map>

template<typename TEventHandler>
class EventManager
{
public:
    template<typename TEvent>
    void dispatch(TEvent e)
    {
        try
        {
            auto cachedDispatcher = cachedDispatchers.at(typeid(e).hash_code());
            cachedDispatcher->dispatch(e);
        }
        catch (std::out_of_range&)
        {
            for (auto [dispatcherTypeHash, d] : dispatchers)
            {
                if (d->canHandleEvent(e))
                {
                    /* Cache event dispatcher for this event type to speed up next handling */
                    cachedDispatchers[typeid(e).hash_code()] = d;

                    d->dispatch(e);

                    /* Do not dispatch message any more if someone has dispatched it */
                    break;
                }
            }
        }
    }

    template<typename TDispatcher, typename TContext>
    void setupContext(TContext ctx)
    {
        if (auto dispatcherItr = dispatchers.find(typeid(TDispatcher).hash_code()); dispatcherItr != dispatchers.end())
        {
            dispatcherItr->second->setupContext(ctx);
            return;
        }

        throw "Failed to setupContext: dispatcher is not registered!";
    }

    template<typename TDispatcher, typename... TDispatcherArgs>
    void registerDispatcher(TDispatcherArgs... args)
    {
        dispatchers[typeid(TDispatcher).hash_code()] = std::make_shared<TDispatcher>((..., args));
    }

protected:
    std::unordered_map<size_t, std::shared_ptr<EventDispatcher<TEventHandler>>> dispatchers;
    std::unordered_map<size_t, std::shared_ptr<EventDispatcher<TEventHandler>>> cachedDispatchers;
};