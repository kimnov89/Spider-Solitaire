#pragma once
#include "Card.h"

class Stack {
public:
    std::vector<Card> stack;
    virtual void AddCard(Card c);
    void AddCardWithStackCoord(Card c);
    Card RemoveCard();
    void RemoveCards(int count);
    void setBeginCoord(int x, int y);
    void AdjustHeight();

protected:
    virtual void UpdateCoordinates();
    int xCoord = 80;
    int yCoord =140;
};

class DrawStack : public Stack{
public:
    void AddCard(Card c) override;
    void setStackDim();
    SDL_Rect getStackDim();
    void UpdateCoordinates() override;
protected:
    SDL_Rect drawStackDim = {0,0,0,0};

};

