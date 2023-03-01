//
// Created by kim on 27-2-23.
//

#include "game.h"

void Game::Run(Controller &controller, Renderer & renderer){
    bool running = true;
    while(running){
        controller.handleInput(running);
        renderer.Render();
    }
}