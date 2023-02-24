#include <iostream>
#include "SDL.h"


//screen dimensions
const int screenWidth = 640;
const int screenHeight = 480;

int main() {
    SDL_Window* window;
    SDL_Surface* screenSurface;

    //Initialize SDL
    if(SDL_Init (SDL_INIT_VIDEO)<0){
        std::cerr<< "SDL could not initialize."<<std::endl;
        std::cerr<< "SDL Error: "<<SDL_GetError()<<std::endl;
    }
    window = SDL_CreateWindow("Spider Solitair", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth,screenHeight, SDL_WINDOW_SHOWN);
    if(window == nullptr){
        std::cerr<<"Window could not be created."<<std::endl;
        std::cerr<<"SDL Error: "<<SDL_GetError()<<std::endl;
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface,nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF ,0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_Event e;
    bool quit = false;
    while( quit == false ){
        while( SDL_PollEvent( &e ) ){
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}