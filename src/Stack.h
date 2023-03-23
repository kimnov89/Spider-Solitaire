#include "Card.h"

class Stack {
public:
    std::vector<Card> stack;
    void AddCard(Card c);
    Card RemoveCard();
    void RemoveCards(int count);
    void setBeginCoord(int x, int y);
private:
    void UpdateCoordinates();
    int xCoord = 80;
    int yCoord =140;
};



