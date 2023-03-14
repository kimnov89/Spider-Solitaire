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
        SpadeDeck.push_back(card);
    }
    //Init CardPool with 8x spade deck cards
    for(int i=0; i<8; i++){
        for(Card c :SpadeDeck){
            CardPool.push_back(c);
        }
    }
    //Shuffle all cards
    auto rng = std::default_random_engine{};
    std::shuffle(CardPool.begin(), CardPool.end(),rng);

    //Init CardDrawStack with 5 times 10 cards
    //all cards in carddrawstack same coordinates
    Card DrawStackCard;
    for(int i=0; i<50; i++){
        DrawStackCard = CardPool.back();
        DrawStackCard.cardDim(80,10,120);
        CardDrawStack.push_back(DrawStackCard);
        CardPool.pop_back();
    }
    //card on top which is in the back of one of the card stacks is visible
    Card stackCard;
    //CardStacks is a vector of 10x CardStack -- 4 of size 6, 6 of size 5
    //cards in CardStacks[0] same coord, cards in CardStacks[1] same coord etc.
    //every card in one of 4 stacks other ycoord
    for(int j=0; j<4; j++) {
        int x = 80 + j * 90;
        for (int i = 0; i < 6; i++) {
            if(i == 5) {
                //card dim of last card with height 120
                stackCard = CardPool.back();
                int y = 140 + i * 15;
                int h = 120;
                stackCard.cardDim(x, y, h);
                CardStack.push_back(stackCard);
                CardPool.pop_back();
            }else{
                stackCard = CardPool.back();
                int y = 140 + i * 15;
                int h = 15;
                stackCard.cardDim(x, y, h);
                CardStack.push_back(stackCard);
                CardPool.pop_back();
            }

        }
        CardStack.back().makeVisible();
        CardStacks.push_back(CardStack);
        CardStack.clear();
    }
    //cards in CardStacks[0] same xcoord, cards in CardStacks[1] same xcoord etc.
    //every card in one of 6 stacks other ycoord
    for(int j=0; j<6; j++){
        int x = 440 + j *90;
        for(int i=0; i<5; i++){
            if(i==4) {
                stackCard = CardPool.back();
                int y = 140 + i * 15;
                int h = 120;
                stackCard.cardDim(x, y, h);
                CardStack.push_back(stackCard);
                CardPool.pop_back();
            }else{
                stackCard = CardPool.back();
                int y = 140 + i * 15;
                int h = 15;
                stackCard.cardDim(x, y, h);
                CardStack.push_back(stackCard);
                CardPool.pop_back();
            }
        }
        CardStack.back().makeVisible();
        CardStacks.push_back(CardStack);
        CardStack.clear();
    }
    //check if CardPool is empty after being divided over all stacks

}

void Spider::Update(SDL_Point &mousePos) {
    //make rectangle out of carddrawstack card dimensions
    SDL_Rect cardDrawStackDim = CardDrawStack.back().cardDim();
    if(SDL_PointInRect(&mousePos,&cardDrawStackDim)){
        DrawCard();
    }else{
        moveSequence(mousePos);
    }
}

void Spider::DrawCard() {
    //card from carddrawstack to top of each card stack
    //carddimensions of card added is carddimension of card in back of stack but y +5
    Card drawStackCard;
    for(int i=0; i<10;i++){
        int xTopCard = CardStacks[i].back().cardDim().x;
        int yTopCard = CardStacks[i].back().cardDim().y;
        CardStacks[i].back().cardDim(xTopCard,yTopCard,15);
        drawStackCard= CardDrawStack.back();
        int x = xTopCard;
        int y = yTopCard+15;
        int h = 120;
        drawStackCard.cardDim(x,y,h);
        drawStackCard.makeVisible();
        CardStacks[i].push_back(drawStackCard);
        CardDrawStack.pop_back();
    }
    std::cout<<"The card draw stack has "<<CardDrawStack.size()<<" cards left"<<std::endl;
}

void Spider::moveSequence(SDL_Point &mousePosition) {
    std::vector<Card> row;
    std::vector<Card> beginningRow;
    std::unique_ptr<std::vector<Card>> selectedStack = std::make_unique<std::vector<Card>>();
    Card selectedCard;
    int index =-1;

    //clicked on one of cards in stack
    auto isSelectedCard = [&](Card &c){ SDL_Rect dim = c.cardDim(); return SDL_PointInRect(&mousePosition,&dim);};
    for(std::vector<Card> cardStack : CardStacks){
        auto iter = std::find_if(cardStack.begin(), cardStack.end(), isSelectedCard);
        if(iter!=cardStack.end()) {
            std::cout<<"selected card found"<<std::endl;
            *selectedStack = cardStack;
            selectedCard = *iter;
            index = std::distance(selectedStack->begin(), iter);
        }else{
            continue;
        }
    }
    Card cardToBeMoved;
    std::vector<Card> rowToBeMoved;
    int topNumber;
    //when selected card is card in back of selected stack then card on top needs to be moved if possible
    if(selectedStack != nullptr && selectedCard.cardDim().x !=0 && index !=-1) {
        if (selectedCard.cardDim().y == selectedStack->back().cardDim().y &&
            selectedCard.CardNumber == selectedStack->back().CardNumber) {
            cardToBeMoved = selectedStack->back();
            topNumber = cardToBeMoved.CardNumber + 1;//number of destination card
        } else {
            //when selected card is not card on top of selected stack, there is a beginning row
            //take row and check if it is a full suit
            std::copy(selectedStack->begin()+index, selectedStack->end(), std::back_inserter(row));
            if (std::is_sorted(row.begin(), row.end())) {
                bool fullSuit = selectedStack->back().CardNumber == 0 && selectedStack->size() > 13 &&
                                (*selectedStack)[selectedStack->size() - 13].CardNumber == 13;
                if (fullSuit) {
                    rowCounter++;
                    selectedStack->erase(selectedStack->begin()+index, selectedStack->end());
                    topNumber = -1;
                } else {
                    rowToBeMoved = row;
                    selectedStack->erase(selectedStack->begin()+index, selectedStack->end());
                    topNumber = rowToBeMoved[0].CardNumber + 1;
                }
            } else {
                //if row is not sorted then card cannot be selected
                return;
            }
        }
    }else{
        return;
    }
    /*
    //find CardStack where card on top has number that is +1 of number of firstvisiblecard
    auto foundDest = std::find_if(CardStacks.begin(),CardStacks.end(), [&](std::vector<Card> &stack){return stack.back().CardNumber == topNumber;});
    if(foundDest == CardStacks.end()){
        return;
    }
    auto& destStack = foundDest;
    //add card or row to destination stack
    //if row to be moved is empty and topNumber is not -1, just a card needs to be moved
    //if row to be moved is empty and topnumber is -1 then a full suit was found and nothing needs to be moved
    //if row to be moved not empty then row needs to be moved
    if(rowToBeMoved.empty()){
        if(topNumber ==-1){
            return;
        }else {
            destStack->push_back(cardToBeMoved);
            selectedStack->pop_back();
        }
    }else{
        destStack->insert(destStack->end(),rowToBeMoved.begin(),rowToBeMoved.end());
    }
    //when everything is moved the card which is now on top of the selectedStack needs to be visible
    if(!(selectedStack->back().getVisibility())) {
        selectedStack->back().makeVisible();
    }*/
}


