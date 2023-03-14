#include "SDL.h"
#include "controller.h"
#include <iostream>
void Controller::handleInput(bool &running){
    //check if clicked on CardRect --> triggers random card on 10 cardstacks in update()
    //check if card dragged on top of another
    SDL_Event e;
    SDL_Point mousePos;
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                running = false;
                break;
            /*case SDL_MOUSEMOTION:
                mousePos = {e.motion.x, e.motion.y};
                break;*/
            case SDL_MOUSEBUTTONDOWN :
                if(e.button.button == SDL_BUTTON_LEFT ) {
                    mousePosition={e.motion.x, e.motion.y};
                    std::cout<<"Mouseposition is "<<mousePosition.x<<","<<mousePosition.y<<std::endl;
                }else{
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(e.button.button == SDL_BUTTON_LEFT){
                    mousePosition = {0,0};
                }else{

                }
                break;
        }
    }
}