# C++ Flelixble Event System

This is a template event library.

## Key features:

- Custom event types
- Custom event hierarchies
- Custom event dispatching policies

## How does it work?

Let's see this in a simple example. 

Imagine you need to develop mouse event system along with keyboard event system. These are different machanisms: mouse click is being propageted from the most top element to the most bottom; whereas keyboard input should only be directed to the focused element (no need to search it).

As you can see we got different dispatching policies: for key and mouse events.

### Create MouseEventDispatcher - dispatching policy

First of all you need to create `MouseEventDispatcher` - it will handle dispatching policy. To do this you need to inherit it from `SpecializedEventDispatcher`. This guy helps to avoid different types conversion.

```c++
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
        /* Use this keyword to access protected data from parent, 
        otherwise you will got a compile error */
        this->m_root->mouse(e);
        return this->m_root;
    }
};
```

Dispatcher can take some construct arguments. They will be provided to dispatcher instance when we will call `EventManager::registerDispatcher()`.

### Create MouseEventHandler - force event handler to implement necessary API

`MouseEventHandler` is responsible for implementing API that your dispatcher can use than. In order to dispatch mouse event (e.g. click), we need to know if element on which click has been made has coordinates of click. So we can ask `this->m_root` for `mouse` method (this simulates check if `m_root` has right coordinates). Than we can handle event based on answer. One more thing to notice is that we also need to be able to iterate through components hierarchy. So we can force this by inheriting from `Hierarchal` in our `MouseEventHandler`. But be carefully! You need to inherit it **virtually**! This is because our `Component` will implement all the `XXXHandler`s and in order to not copy base class we need to inherit virtually.

```c++
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
    /* E.g. this can be used to check coorinates, to modify them to local and so on... */
    virtual bool mouse(const MouseEvent& e) = 0;
};
```

### Create MouseContext - can be passed to MouseEventDispatcher

If you need to pass some information to event dispatcher, you have to implement `setupContext()` method in you `MouseEventDispatcher`. For more details see `SpecializedEventDispatcher` and `EventDispatcher` implementation.

```c++

struct BaseContext
{};

struct KeyboardContext
    :
    BaseContext
{
    int focusedComponent = 321;
};

class KeyboardEventHandler 
    ...
{
    ... 

    virtual void p_setupContext(KeyboardContext ctx)
    {
        m_focusedComponent = ctx.focusedComponent;
    }

private:
    int m_focusedComponent = 0;
};
```


```c++
struct BaseContext
{};

struct MouseContext
    :
    BaseContext
{
    int mouseInfo = 1;
};
```

### Inherit and implement MouseEventHandler by your actual handler

```c++
#pragma once

#include "KeyboardEventHandler.h"
#include "MouseEventHandler.h"


#include <iostream>

class Component
    :
    public KeyboardEventHandler<Component>,
    public MouseEventHandler<Component>
{
public:
    virtual void handleEvent(const CoreEvent& e) const override {}
    virtual std::shared_ptr<Component> getParent() override { return nullptr; }
    virtual std::vector<std::shared_ptr<Component>> getChildren() override { return {}; }
    virtual void mouse(const MouseEvent& e) override 
    {
        std::cout << "Handle mouse method required by MouseEventHandler: \n";
        std::cout << e.x << " " << e.y;
    }
    virtual void key(const KeyboardEvent& e) override
    {
        std::cout << "Handle key method required by KeyboardEventHandler: \n";
        std::cout << e.key;
    }
};
```

### Use it!

```c++

...

// Create component somewhere
auto component = std::make_shared<Component>();


...

// Create event manager somewhere else
EventManager<Component> em;

// Register all your event dispatchers
em.registerDispatcher<KeyboardEventDispatcher<Component>>(component);
em.registerDispatcher<MouseEventDispatcher<Component>>(component);


...

// If your need to setup context anywhere else

em.setupContext<KeyboardEventDispatcher<Component>>(KeyboardContext());

...

// Some where create event and call dispatch
em.dispatch(MouseButtonEvent());

```

That's all!

### All copyrights reserved 2020
Designed, implemented by [maxnevans](https://github.com/maxnevans).