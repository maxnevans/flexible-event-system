#pragma once

struct BaseContext
{
};

struct KeyboardContext
    :
    BaseContext
{
    int focusedComponent = 321;
};

struct MouseContext
    :
    BaseContext
{
    int mouseInfo = 1;
};