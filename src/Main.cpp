#include "Component.h"
#include "KeyboardEventDispatcher.h"
#include "MouseEventDispatcher.h"
#include "EventManager.h"

int main()
{
    auto component = std::make_shared<Component>();

    EventManager<Component> em;

    em.registerDispatcher<KeyboardEventDispatcher<Component>>(component);
    em.registerDispatcher<MouseEventDispatcher<Component>>(component);

    em.setupContext<KeyboardEventDispatcher<Component>>(KeyboardContext());

    em.dispatch(MouseButtonEvent());

    return 0;
}