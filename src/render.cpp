#include "render.h"
#include <vector>
#include <filesystem>
#include <algorithm>

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
    //Create Textures -- textures of all images in map with int for cardnumbers
    std::string path="../images/";
    std::vector<std::string> imgNames;
    SDL_Texture* imgTexture;
    std::filesystem::path imgDir{path};
    if(std::filesystem::exists(imgDir)) {
        for (auto &dir_entry: std::filesystem::directory_iterator{imgDir}) {
            std::string dirName = dir_entry.path().filename();
            imgNames.push_back(dirName);
        }
    }
    std::sort(imgNames.begin(),imgNames.end(),[](const std::string &a, const std::string &b){return a<b;});
    for(int i=0;i<imgNames.size();i++) {
        imgTexture = IMG_LoadTexture(sdlRenderer,path.c_str());
        if (imgTexture == nullptr) {
            SDL_DestroyRenderer(sdlRenderer);
            SDL_DestroyWindow(sdlWindow);
            std::cerr << "Image could not be loaded." << std::endl;
            std::cerr << "IMG Error: " << IMG_GetError() << std::endl;
            SDL_Quit();
        } else {
            imageTextures.insert({i, imgTexture});
        }
    }
}

void Renderer::renderTexture(int x, int y, int width, int height, SDL_Texture *txtr) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = width;
    dst.h = height;
    SDL_RenderCopy(sdlRenderer, txtr, NULL, &dst);
}

void Renderer::Render(const std::vector<std::vector<Card>> &CardStacks, const std::vector<Card> &CardDrawStack, int rowCount){
    SDL_RenderClear(sdlRenderer);
    SDL_Texture* textureBackImg = imageTextures[13];
    if(!CardDrawStack.empty()) {
        SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
        renderTexture(CardDrawStack[0].cardDim().x, CardDrawStack[0].cardDim().y, CardDrawStack[0].cardDim().w,
                      CardDrawStack[0].cardDim().h,textureBackImg);
    }

    //for each stack in cardStacks render all cards
    /*for(const auto& stack : CardStacks){
        for(auto card : stack){
            if(card.getVisibility()) {
                switch (card.CardNumber) {
                    case 1:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h,imageTextures[0]);
                        break;
                    case 2:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h,imageTextures[1]);
                        break;
                    case 3:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h,imageTextures[2]);
                        break;
                    case 4:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h,imageTextures[3]);
                        break;
                    case 5:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h,imageTextures[4]);
                        break;
                    case 6:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h, imageTextures[5]);
                        break;
                    case 7:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h, imageTextures[6]);
                        break;
                    case 8:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h, imageTextures[7]);
                        break;
                    case 9:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h, imageTextures[8]);
                        break;
                    case 10:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h, imageTextures[9]);
                        break;
                    case 11:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h, imageTextures[10]);
                        break;
                    case 12:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h, imageTextures[11]);
                        break;
                    case 13:
                        renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h, imageTextures[12]);
                        break;
                }
            }else{
                renderTexture(card.cardDim().x, card.cardDim().y, card.cardDim().w,card.cardDim().h,textureBackImg);
            }

        }
    }*/
    SDL_RenderPresent(sdlRenderer);
}

Renderer::~Renderer(){
    for(int i=0; i<imageTextures.size();i++) {
        SDL_DestroyTexture(imageTextures[i]);
        imageTextures[i] = nullptr;
    }
    //SDL_DestroyTexture(sdlTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    sdlRenderer = nullptr;
    //sdlTexture = nullptr;
    sdlWindow = nullptr;
    IMG_Quit();
    SDL_Quit();
}