#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>
#include "SDL.h"

class Controller {
public:
    void handleInput(bool &running);
    SDL_Point mousePosition;
    bool leftMouseButtonDown = false;
};


#endif CONTROLLER_H
