#pragma once
#include "controller.h"
#include "render.h"
#include "Spider.h"

class Game {
public:
    void Run(Renderer &renderer, Controller &controller,  std::size_t target_frame_duration);
private:
    Spider itsyBitsy;
    SDL_Point mousePosition;
};
