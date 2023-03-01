#include <iostream>
#include "controller.h"
#include "game.h"
#include <fstream>

int main() {
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{480};
    constexpr std::size_t kTileSize{40};
    Renderer renderer(kScreenWidth,kScreenHeight, kTileSize);
    Controller controller;
    Game game;
    game.Run(controller, renderer);

    return 0;
}