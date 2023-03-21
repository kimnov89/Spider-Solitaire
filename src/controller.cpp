#include "SDL.h"
#include "controller.h"
#include <iostream>
void Controller::handleInput(bool &running){
    //check if clicked on CardRect --> triggers random card on 10 cardstacks in update()
    //check if card dragged on top of another
    SDL_Event e;
    bool leftMouseButtonDown = false;
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN :
                if( e.button.button == SDL_BUTTON_LEFT ) {
                    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
                    std::cout<<"Mouseposition is "<<mousePosition.x<<","<<mousePosition.y<<std::endl;
                    break;
                }else{
                    break;
                }
            case SDL_MOUSEBUTTONUP:
                if(e.button.button == SDL_BUTTON_LEFT) {
                    std::cout << "mouse button up detected"<<std::endl;
                    mousePosition = {0, 0};
                }
                break;
        }
    }
}