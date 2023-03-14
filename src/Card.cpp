#include "Card.h"
Card::Card() {
    isVisible = false;
};

void Card::makeVisible() {
    isVisible = true;
}

void Card::cardDim(int x, int y) {
    cardDimension = {x, y, 80, 120};
}

SDL_Rect  Card::cardDim() {
    return cardDimension;
}

bool Card::getVisibility() {
        return isVisible;
}