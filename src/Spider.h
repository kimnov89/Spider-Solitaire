#ifndef SDL2TEST_SPIDER_H
#define SDL2TEST_SPIDER_H
#include "Card.h"
#include <vector>

class Spider {
public:
    Spider();
    void Init();
    void DrawCard();
    void moveSequence(SDL_Point &mousePosition);
    void Update(SDL_Point &mousePos);
    std::vector<Card> CardPool;//8 x 13 spade cards = 104 cards
    std::vector<Card> CardStack;//4x 6 Cards, 6x5 Cards -- 54
    std::vector<std::vector<Card>> CardStacks;
    std::vector<Card> CardDrawStack;//50
    std::vector<Card> SpadeDeck;
    int rowCounter;
};


#endif //SDL2TEST_SPIDER_H
