#pragma once

#include "SDL.h"

#include <string.h>
#include <iostream>

class InputManager
{
public:

    InputManager() {}
    ~InputManager() {}

    void inputEvent();

private:

    SDL_Event event;
};