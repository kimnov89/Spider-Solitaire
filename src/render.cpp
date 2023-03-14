#include "render.h"
#include <vector>

Renderer::Renderer(const std::size_t screenWidth, const std::size_t screenHeight): screenWidth(screenWidth), screenHeight(screenHeight){
    //Initilaize SDL
    if(SDL_Init (SDL_INIT_VIDEO)<0){
        std::cerr<< "SDL could not initialize."<<std::endl;
        std::cerr<< "SDL Error: "<<SDL_GetError()<<std::endl;
        SDL_Quit();
    }
    //Initialize Image
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        std::cerr<<"SDL could not initialize PNG."<<std::endl;
        std::cerr<<"SDL Error: "<<IMG_GetError()<<std::endl;
        IMG_Quit();
    }

    //Create Window
    sdlWindow = SDL_CreateWindow("Spider Solitair", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth,
                              screenHeight, SDL_WINDOW_SHOWN);
    if (sdlWindow == nullptr) {
        std::cerr << "Window could not be created." << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    //Create Renderer
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdlRenderer == nullptr) {
        SDL_DestroyWindow(sdlWindow);
        std::cerr << "Renderer could not be created." << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }


}

void Renderer::renderTexture(int x, int y, int width, int height) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = width;
    dst.h = height;
    SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &dst);
}
void Renderer::LoadTexture(std::string path){
    sdlTexture = IMG_LoadTexture(sdlRenderer,path.c_str());
    if (sdlTexture == nullptr) {
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(sdlWindow);
        std::cerr << "Image could not be loaded." << std::endl;
        std::cerr << "IMG Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
    }
}
void Renderer::Render(std::vector<std::vector<Card>> &CardStacks, std::vector<Card> &CardDrawStack, int &rowCount){
    //back of cards for card draw stack
    SDL_RenderClear(sdlRenderer);
    //Create texture from image
    std::string path = "../images/back.png";
    LoadTexture(path);

    if(!CardDrawStack.empty()) {
        SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
        renderTexture(CardDrawStack[0].cardDim().x, CardDrawStack[0].cardDim().y, CardDrawStack[0].cardDim().w,
                      CardDrawStack[0].cardDim().h);
    }

    //for each stack in cardStacks render all cards
    for(auto stack : CardStacks){
        renderTexture(stack[0].cardDim().x,stack[0].cardDim().y,stack[0].cardDim().w,stack[0].cardDim().h);
        for(auto card : stack){
            if(card.getVisibility()) {
                switch (card.CardNumber) {
                    case 1:
                        LoadTexture("../images/ace_of_spades2.png");
                        break;
                    case 2:
                        LoadTexture("../images/2_of_spades.png");
                        break;
                    case 3:
                        LoadTexture("../images/3_of_spades.png");
                        break;
                    case 4:
                        LoadTexture("../images/4_of_spades.png");
                        break;
                    case 5:
                        LoadTexture("../images/5_of_spades.png");
                        break;
                    case 6:
                        LoadTexture("../images/6_of_spades.png");
                        break;
                    case 7:
                        LoadTexture("../images/7_of_spades.png");
                        break;
                    case 8:
                        LoadTexture("../images/8_of_spades.png");
                        break;
                    case 9:
                        LoadTexture("../images/9_of_spades.png");
                        break;
                    case 10:
                        LoadTexture("../images/10_of_spades.png");
                        break;
                    case 11:
                        LoadTexture("../images/jack_of_spades2.png");
                        break;
                    case 12:
                        LoadTexture("../images/queen_of_spades2.png");
                        break;
                    case 13:
                        LoadTexture("../images/king_of_spades2.png");
                        break;
                }
            }else{
                LoadTexture("../images/back.png");
            }
            renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h);
        }
    }
    SDL_RenderPresent(sdlRenderer);
}

Renderer::~Renderer(){
    SDL_DestroyTexture(sdlTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    sdlRenderer = nullptr;
    sdlTexture = nullptr;
    sdlWindow = nullptr;
    IMG_Quit();
    SDL_Quit();
}