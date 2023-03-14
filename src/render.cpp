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
    if (sdlTexture != nullptr)
    {
        SDL_DestroyTexture(sdlTexture);
    }
    sdlTexture = IMG_LoadTexture(sdlRenderer,path.c_str());
    if (sdlTexture == nullptr) {
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(sdlWindow);
        std::cerr << "Image could not be loaded." << std::endl;
        std::cerr << "IMG Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
    }
}
void Renderer::Render(const std::vector<std::vector<Card>> &CardStacks, const std::vector<Card> &CardDrawStack, int rowCount){
    SDL_RenderClear(sdlRenderer);
    std::string path = "../images/back.png";
    if(!CardDrawStack.empty()) {
        LoadTexture(path);
        SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
        renderTexture(CardDrawStack[0].cardDim().x, CardDrawStack[0].cardDim().y, CardDrawStack[0].cardDim().w,
                      CardDrawStack[0].cardDim().h);
    }

    //for each stack in cardStacks render all cards
    for(const auto& stack : CardStacks){
        for(auto card : stack){
            if(card.getVisibility()) {
                switch (card.CardNumber) {
                    case 1:
                        path = "../images/ace_of_spades2.png";
                        break;
                    case 2:
                        path = "../images/2_of_spades.png";
                        break;
                    case 3:
                        path = "../images/3_of_spades.png";
                        break;
                    case 4:
                        path = "../images/4_of_spades.png";
                        break;
                    case 5:
                        path ="../images/5_of_spades.png";
                        break;
                    case 6:
                        path ="../images/6_of_spades.png";
                        break;
                    case 7:
                        path ="../images/7_of_spades.png";
                        break;
                    case 8:
                        path = "../images/8_of_spades.png";
                        break;
                    case 9:
                        path ="../images/9_of_spades.png";
                        break;
                    case 10:
                        path ="../images/10_of_spades.png";
                        break;
                    case 11:
                        path ="../images/jack_of_spades2.png";
                        break;
                    case 12:
                        path ="../images/queen_of_spades2.png";
                        break;
                    case 13:
                        path ="../images/king_of_spades2.png";
                        break;
                }
            }else{
                path ="../images/back.png";
            }
            LoadTexture(path);
            renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h);
        }
    }
    SDL_RenderPresent(sdlRenderer);
    SDL_DestroyTexture(sdlTexture);
    sdlTexture = nullptr;
}

Renderer::~Renderer(){
    //SDL_DestroyTexture(sdlTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    sdlRenderer = nullptr;
    sdlTexture = nullptr;
    sdlWindow = nullptr;
    IMG_Quit();
    SDL_Quit();
}