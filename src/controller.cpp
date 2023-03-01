//
// Created by kim on 27-2-23.
//
#include "SDL.h"
#include "controller.h"
void Controller::handleInput(bool &running){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            running = false;
        }
        SDL_Rect* selectedRect;
        bool leftMouseButtonDown = false;
        SDL_Point mousePos;
    }
}