#ifndef CARD_H
#define CARD_H
#include "SDL.h"
class Card {
public:
    Card();
    int CardNumber; //Ace to King
    void cardDim(int x, int y);
    SDL_Rect cardDim();
    void makeVisible();
    bool getVisibility();
    bool operator<(Card& card){
        return (CardNumber < card.CardNumber);
    }
private:
    SDL_Rect cardDimension;
    bool isVisible; //visible front or invisible back
};
#endif CARD_H
