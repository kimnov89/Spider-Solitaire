#include "Stack.h"
void Stack::AddCard(Card c) {
    stack.emplace_back(c);
    UpdateCoordinates();
}

void Stack::UpdateCoordinates() {
    for (int i = 0; i < stack.size(); i++) {
        int y = yCoord + i * 15;
        stack[i].cardDim(xCoord, y, i == stack.size()-1 ? 120 : 15);
    }
}

void Stack::setBeginCoord(int x, int y) {
        xCoord = x;
        yCoord = y;
}

Card Stack::RemoveCard() {
    Card topCard = stack.back();
    stack.pop_back();
    UpdateCoordinates();
    if(!stack.empty()){
        stack.back().makeVisible();
    }
    return topCard;
}

void Stack::RemoveCards(int count) {
    for(int i=0; i<count; i++){
        RemoveCard();
    }

}

void Stack::AddCardWithStackCoord(Card c) const {
    c.cardDim(xCoord,yCoord,15);
}


