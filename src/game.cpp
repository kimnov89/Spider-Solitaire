
#include "game.h"

void Game::Run(Renderer & renderer, Controller &controller, Spider &spider, std::size_t target_frame_duration){
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    bool running = true;

    while(running){
        frame_start = SDL_GetTicks();
        controller.handleInput(running);
        //update spider deck with mousepoint
        spider.Update(controller.mousePosition);
        renderer.Render(spider.CardStacks, spider.CardDrawStack, spider.rowCounter);//take cardstacks, carddrawstack, rowCounter

        frame_end = SDL_GetTicks();

        frame_duration = frame_end - frame_start;
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }

    }
}
