#include <algorithm>
#include "Stack.h"

void Stack::AddCard(Card c) {
    stack.emplace_back(c);
    UpdateCoordinates();
}

void Stack::UpdateCoordinates() {
    for (int i = 0; i < stack.size(); i++) {
        int y = yCoord + i * yIncrement;
        stack[i].cardDim(xCoord, y, i == stack.size()-1 ? 120 : yIncrement);
    }
}

void Stack::setBeginCoord(int x, int y) {
        xCoord = x;
        yCoord = y;
}

Card Stack::RemoveCard(bool topCardVisible) {
    Card topCard = stack.back();
    stack.pop_back();
    UpdateCoordinates();
    if(!stack.empty()&& topCardVisible){
        stack.back().makeVisible();
    }
    return topCard;
}

void Stack::RemoveCards(int count) {
    for(int i=0; i<count; i++){
        RemoveCard();
    }
}

void Stack::setYIncrement(int incr) {
    yIncrement = incr;
}

bool Stack::topCardsAreFullSuit() const {
    if (stack.size() < 13)
        return false;

    bool top13CardsAreSorted = std::is_sorted(stack.end()-13, stack.end());
    bool top13CardsRangeFromKingToAce = stack.back().CardNumber == 1;
    bool allCardsAreVisible = stack[stack.size() - 13].getVisibility();
    bool fullSuit = top13CardsAreSorted && top13CardsRangeFromKingToAce && allCardsAreVisible;

    return fullSuit;
}

