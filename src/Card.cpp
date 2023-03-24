#include "Card.h"
Card::Card() {
    isVisible = false;
    cardDimension = {0,0,0,0};
};

void Card::makeVisible() {
    isVisible = true;
}

void Card::cardDim(SDL_Rect dim) {
    cardDimension = dim;
}

void Card::cardDim(int x, int y, int h) {
    cardDimension = {x,y,80,h};
}

SDL_Rect  Card::cardDim() const {
    return cardDimension;
}

bool Card::getVisibility() const {
        return isVisible;
}

int Card::getFullHeight() const {
    return kFullCardHeight;
}

