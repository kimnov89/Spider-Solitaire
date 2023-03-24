#include "game.h"
#include <algorithm>

int main() {
    constexpr std::size_t kScreenWidth{1280};
    constexpr std::size_t kScreenHeight{960};
    constexpr std::size_t kFramesPerSecond{10};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    Renderer renderer(kScreenWidth,kScreenHeight);
    Controller controller{};
    //sorting from ace to king
    Game game;
    game.Run(renderer, controller, kMsPerFrame);


    return 0;
}