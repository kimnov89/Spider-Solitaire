#include "Card.h"
Card::Card() {
    isVisible = false;
    cardDim(0,0,0);
};

void Card::makeVisible() {
    isVisible = true;
}

void Card::cardDim(int x, int y, int h) {
    cardDimension = {x, y, 80, h};
}

SDL_Rect  Card::cardDim() {
    return cardDimension;
}

bool Card::getVisibility() {
        return isVisible;
}