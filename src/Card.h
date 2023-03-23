#pragma once
#include <vector>
#include "SDL.h"
class Card {
public:
    Card();
    int CardNumber;
    void cardDim(SDL_Rect dim);
    void cardDim(int x, int y, int h);
    [[nodiscard]] SDL_Rect cardDim() const;
    void makeVisible();
    [[nodiscard]] bool getVisibility() const;
    bool operator<(Card& card) const {
        return (card.CardNumber < CardNumber);
    }
private:
    SDL_Rect cardDimension;
    bool isVisible; //visible front or invisible back
};
