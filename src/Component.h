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