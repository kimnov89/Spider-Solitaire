#pragma once
#include <vector>
#include "SDL.h"

class Controller {
public:
    void handleInput(bool &running);
    SDL_Point mousePosition;
    bool leftMouseButtonDown = false;
};
