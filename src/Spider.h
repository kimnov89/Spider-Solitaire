#ifndef SDL2TEST_SPIDER_H
#define SDL2TEST_SPIDER_H
#include "Card.h"
#include "Stack.h"
#include <vector>

class Spider {
public:
    Spider();
    void Init();
    void DrawCard();
    void moveSequence(SDL_Point &mousePosition);
    void Update(SDL_Point &mousePos);
    std::vector<Card> CardPool;//8 x 13 spade cards = 104 cards
    std::vector<Stack> CardStacks;
    Stack CardDrawStack;//50
    std::vector<Card> SpadeDeck;
    int rowCounter;
};


#endif //SDL2TEST_SPIDER_H
