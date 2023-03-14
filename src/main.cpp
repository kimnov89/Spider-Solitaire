#include <iostream>
#include "controller.h"
#include "game.h"
#include "Spider.h"
#include "Card.h"
#include <algorithm>

int main() {
    constexpr std::size_t kScreenWidth{1280};
    constexpr std::size_t kScreenHeight{960};
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    Renderer renderer(kScreenWidth,kScreenHeight);
    Controller controller;
    Spider spidy;
    spidy.Init();
    //sorting from ace to king
    if(std::is_sorted(spidy.SpadeDeck.begin(),spidy.SpadeDeck.end())){
        std::cout<<"Spade card stack is sorted"<<std::endl;
    }else{
        std::cout<<"Spade card deck is not sorted"<<std::endl;
    }
    std::cout<<"The Card deck has "<<spidy.CardPool.size()<<" cards"<<std::endl;
    std::cout<<"The Card draw deck has "<<spidy.CardDrawStack.size()<<" cards"<<std::endl;
    std::cout<<"The game has "<<spidy.CardStacks.size()<<" card stacks"<<std::endl;
    std::cout<<"The 4th card stack has "<<spidy.CardStacks[3].size()<<" cards"<<std::endl;
    std::cout<<"The 10th stack has "<<spidy.CardStacks[9].size()<<" cards"<<std::endl;
    Game game;
    game.Run(renderer, controller, spidy, kMsPerFrame);


    return 0;
}