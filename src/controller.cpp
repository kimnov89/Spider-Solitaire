#include "SDL.h"
#include "controller.h"
#include <iostream>
void Controller::handleInput(bool &running){
    //check if clicked on CardRect --> triggers random card on 10 cardstacks in update()
    //check if card dragged on top of another
    SDL_Event e;
    mousePosition = {0, 0};
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN :
                if( e.button.button == SDL_BUTTON_LEFT ) {
                    leftMouseButtonDown = true;
                    std::cout<<"Mouseposition is "<<mousePosition.x<<","<<mousePosition.y<<std::endl;
                    break;
                }else{
                    break;
                }
            case SDL_MOUSEBUTTONUP:
                if(e.button.button == SDL_BUTTON_LEFT && leftMouseButtonDown) {
                    std::cout << "mouse button up detected"<<std::endl;
                    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
                    leftMouseButtonDown = false;

                }
                break;
        }
    }
}