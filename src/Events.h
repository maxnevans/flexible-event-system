#pragma once

struct CoreEvent
{
    virtual void _() const {} // To make CoreEvent polymorphic
};

struct KeyboardEvent
    :
    public CoreEvent
{
    int key = 0;
};

struct InputEvent
    :
    public KeyboardEvent
{
    int ch = 123;
};

struct MouseEvent
    :
    public CoreEvent
{
    int x = 10;
    int y = 100;
};

struct MouseButtonEvent
    :
    public MouseEvent
{
    int button = 1;
};

struct MouseWheelEvent
    :
    public MouseEvent
{
    int wheel = 123;
};