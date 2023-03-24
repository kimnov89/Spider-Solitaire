#pragma once
#include "Card.h"

class Stack {
public:
    std::vector<Card> stack;
    void AddCard(Card c);
    void AddCardWithStackCoord(Card c) const;
    Card RemoveCard();
    void RemoveCards(int count);
    void setBeginCoord(int x, int y);
private:
    void UpdateCoordinates();
    void UpdateHeight();
    int xCoord = 80;
    int yCoord =140;
};



