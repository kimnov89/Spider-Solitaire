#include "Spider.h"
#include "Card.h"
#include "SDL.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <memory>

Spider::Spider(){
    Init();
    rowCounter=0;
}

void Spider::Init() {
    //Init spade deck
    Card card;
    for(int i=1; i<=13; i++){
        card.CardNumber = i;
        SpadeDeck.emplace_back(card);
    }
    //Init CardPool with 8x spade deck cards
    for(int i=0; i<8; i++){
        for(Card c :SpadeDeck){
            CardPool.emplace_back(c);
        }
    }
    //Shuffle all cards
    auto rng = std::default_random_engine{};
    std::shuffle(CardPool.begin(), CardPool.end(),rng);

    //Init CardDrawStack with 5 times 10 cards, vector of 5 stacks a 10 cards , cards same coordinates as stack, stack yCoordinates = y + j*15
    //stack.back() h coord 15 or 120
    for(int j=0; j<5; j++) {
        int x = 10 + j * 15;
        CardDrawStack.setBeginCoord(x, 10);
        for (int i = 0; i < 10; i++) {
            Card DrawStackCard = CardPool.back();
            CardDrawStack.AddCardWithStackCoord(DrawStackCard);
            CardPool.pop_back();
        }
    }
    //card on top which is in the back of one of the card stacks is visible
    //CardStacks is a vector of 10x CardStack -- 4 of size 6, 6 of size 5
    //cards in CardStacks[0] same coord, cards in CardStacks[1] same coord etc.
    //every card in one of 4 stacks other ycoord
    for(int j=0; j<10; j++) {
        int x = 80 + j * 90;
        Stack CardStack;
        CardStack.setBeginCoord(x,140);
        int nrCards =5;
        if(j<=4) {
            nrCards = 6;
        }
            for (int i = 0; i < nrCards; i++) {
                Card stackCard = CardPool.back();
                CardStack.AddCard(stackCard);
                CardPool.pop_back();
            }
        CardStack.stack.back().makeVisible();
        CardStacks.emplace_back(CardStack);
    }
}
//TODO: Change Update and DrawCard with new CardDrawStack
void Spider::Update(SDL_Point &mousePos) {
    //make rectangle out of carddrawstack card dimensions
    SDL_Rect cardDrawStackDim = CardDrawStack.stack.back().cardDim();
    bool mouseInCardDrawStack = SDL_PointInRect(&mousePos,&cardDrawStackDim);
    if(mouseInCardDrawStack){
        DrawCard();
    }else{
        moveSequence(mousePos);
    }
}

void Spider::DrawCard() {
    //card from carddrawstack to top of each card stack
    //carddimensions of card added is carddimension of card in back of stack but y +5
    for(int i=0; i<10;i++){
        Card drawStackCard= CardDrawStack.stack.back();
        drawStackCard.makeVisible();
        CardStacks[i].AddCard(drawStackCard);
        CardDrawStack.stack.pop_back();
    }
    std::cout<<"The card draw stack has "<<CardDrawStack.stack.size()<<" cards left"<<std::endl;
}

void Spider::moveSequence(SDL_Point &mousePosition) {
    std::vector<Card> row;
    std::vector<Card> beginningRow;
    Stack* selectedStack = nullptr;
    Card selectedCard;
    int index =-1;

    //full suit check not when clicked but when top card is ace
    for(Stack &stack: CardStacks){
        bool fullSuit = stack.stack.size()>=13 && std::is_sorted(stack.stack.end()-13, stack.stack.end()) && stack.stack.back().CardNumber ==0 && stack.stack[stack.stack.size()-13].CardNumber ==13;
        if(fullSuit && stack.stack[stack.stack.size()-13].getVisibility()){
            std::cout<<"Full suit found"<<std::endl;
            stack.RemoveCards(13);
            rowCounter++;
        }
    }
    //clicked on one of cards in stack
    auto isSelectedCard = [&](Card &c){ SDL_Rect dim = c.cardDim(); return SDL_PointInRect(&mousePosition,&dim);};
    for(Stack & cardStack : CardStacks){
        auto iter = std::find_if(cardStack.stack.begin(), cardStack.stack.end(), isSelectedCard);
        if(iter!=cardStack.stack.end()) {
            std::cout<<"selected card found"<<std::endl;
            selectedStack = &cardStack;
            selectedCard = *iter;
            std::cout<<"The selected card is "<<selectedCard.CardNumber<<std::endl;
            index = std::distance(selectedStack->stack.begin(), iter);
            break;
        }
    }

    Card cardToBeMoved;
    std::vector<Card> rowToBeMoved;
    int topNumber;
    //when selected card is card in back of selected stack then card on top needs to be moved if possible
    if (selectedStack != nullptr) {
        if (selectedStack->stack.empty()) {
            std::cerr << "Selected stack is empty. This should not happen\n";
            return;
        }
        bool selectedCardIsOnTop = selectedCard.cardDim().y == selectedStack->stack.back().cardDim().y && selectedCard.cardDim().h == selectedStack->stack.back().cardDim().h && selectedCard.CardNumber == selectedStack->stack.back().CardNumber;
        if (selectedCardIsOnTop) {
            cardToBeMoved = selectedStack->stack.back();
            if(cardToBeMoved.CardNumber ==13){
                topNumber == -1;
            }else {
                topNumber = cardToBeMoved.CardNumber + 1;//number of destination card
            }
        } else {
            //when selected card is not card on top of selected stack, there is a beginning row
            std::copy(selectedStack->stack.begin()+index, selectedStack->stack.end(), std::back_inserter(row));
            if (std::is_sorted(row.begin(), row.end())) {
                    if (row[0].CardNumber == 13) {
                        topNumber == -1;
                    } else {
                        rowToBeMoved = row;
                        if (rowToBeMoved.empty()) {
                            std::cerr << "RowToBeMoved is empty. This should not have happened\n";
                        }
                        topNumber = rowToBeMoved[0].CardNumber + 1;
                        std::cout << "Part of suit found, starting at " << rowToBeMoved[0].CardNumber << "\n";
                    }
            } else {
                //if row is not sorted then card cannot be selected
                return;
            }
        }
    }else{
        return;
    }
    //when topNumber is -1 then king on top or part of suit with king at the bottom -- can only be moved if a stack is empty
    auto emptyDest = std::find_if(CardStacks.begin(), CardStacks.end(), [&](Stack &stack) {return stack.stack.empty();});

    //find CardStack where card on top has number that is +1 of number of firstvisiblecard
    auto foundDest = std::find_if(CardStacks.begin(),CardStacks.end(), [&](Stack &stack){return stack.stack.back().CardNumber == topNumber;});
    if(foundDest == CardStacks.end()){
        return;
    }
    auto destStack = &(*foundDest);
    //add card or row to destination stack
    //if row to be moved is empty and topNumber is not -1, just a card needs to be moved
    //if row to be moved is empty and topnumber is -1 then a full suit was found and nothing needs to be moved
    //if row to be moved not empty then row needs to be moved
    std::cout<<"The top card on the selected stack is now "<<selectedStack->stack.back().CardNumber<<std::endl;
    std::cout<<"The top card on the destination stack is now "<<destStack->stack.back().CardNumber<<std::endl;
    //coordinates of cards need to be changed when moved -- cardToBeMoved needs dimensions of top card on dest stack with y dimension+15
    if(rowToBeMoved.empty()){
        if(topNumber == -1 && !(emptyDest == CardStacks.end())){
            emptyDest->AddCard(selectedStack->RemoveCard());
        }else if(topNumber == -1 && emptyDest == CardStacks.end()){
            return;
        }else {
            destStack->AddCard(selectedStack->RemoveCard());
        }
    }else{
        if(topNumber == -1 && !(emptyDest == CardStacks.end())){
            for(int i = 0; i<=rowToBeMoved.size();i++){
                emptyDest->AddCard(rowToBeMoved.front());
                selectedStack->RemoveCard();
            }
        }else if(topNumber == -1 && emptyDest == CardStacks.end()){
            return;
        }else {
            for (int i = 0; i <= rowToBeMoved.size(); i++) {
                destStack->AddCard(rowToBeMoved.front());
                selectedStack->RemoveCard();
            }
        }
    }
    //when everything is moved the card which is now on top of the selectedStack needs to be visible
}


