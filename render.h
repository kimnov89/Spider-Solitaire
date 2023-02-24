#ifndef RENDER_H
#define RENDER_H
#include<iostream>
#include <string>
#include "SDL.h"

class Render {
public:
    Render(const std::size_t screenWidth, const std::size_t screenHeight);
    ~Render();
    void Rendering();
    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
    const std::size_t screenWidth;
    const std::size_t screenHeight;

};


#endif RENDER_H
