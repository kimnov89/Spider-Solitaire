//
// Created by kim on 27-2-23.
//
#include "SDL.h"
#include "controller.h"
void Controller::handleInput(bool &running){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        SDL_Rect CardRect = {80,100,40,60};
        SDL_Rect* selectedRect;
        bool leftMouseButtonDown = false;
        SDL_Point mousePos;
        switch(e.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEMOTION:
                mousePos = {e.motion.x, e.motion.y};
                break;
            case SDL_MOUSEBUTTONUP:
                if(leftMouseButtonDown && e.button.button == SDL_BUTTON_LEFT){
                    leftMouseButtonDown = false;
                    selectedRect = nullptr;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(!leftMouseButtonDown && e.button.button == SDL_BUTTON_LEFT){
                    leftMouseButtonDown = true;
                    if (SDL_PointInRect(&mousePos,&CardRect)){
                        selectedRect = &CardRect;
                        break;
                    }
                }
                break;
        }
    }
}