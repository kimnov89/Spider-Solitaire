#pragma once
#include "Card.h"

class Stack {
public:
    std::vector<Card> stack;
    void AddCard(Card c);
    Card RemoveCard(bool topCardVisible = true);
    void RemoveCards(int count);
    void setBeginCoord(int x, int y);
    void setYIncrement(int incr);
    bool topCardsAreFullSuit() const;
protected:
    virtual void UpdateCoordinates();
    int xCoord = 80;
    int yCoord =140;
    int yIncrement = 15;
};

