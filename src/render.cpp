#include "render.h"
#include <vector>

Renderer::Renderer(const std::size_t screenWidth, const std::size_t screenHeight, const std::size_t tileSize): screenWidth(screenWidth), screenHeight(screenHeight), tileSize(tileSize){
    //Initilaize SDL
    if(SDL_Init (SDL_INIT_VIDEO)<0){
        std::cerr<< "SDL could not initialize."<<std::endl;
        std::cerr<< "SDL Error: "<<SDL_GetError()<<std::endl;
    }
    //Initialize Image
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        std::cerr<<"SDL could not initialize PNG."<<std::endl;
        std::cerr<<"SDL Error: "<<IMG_GetError()<<std::endl;
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
    //Create texture from image
    std::string path = "../images/ace.png";
    sdlTexture = IMG_LoadTexture(sdlRenderer,path.c_str());
    if (sdlTexture == nullptr) {
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(sdlWindow);
        std::cerr << "Image could not be loaded." << std::endl;
        std::cerr << "IMG Error: " <<IMG_GetError() << std::endl;
        SDL_Quit();
    }

}
void Renderer::renderTiles(){
    int y = 140;
    std::vector<int> xCoordinates;
    SDL_RenderClear(sdlRenderer);
    for(int i =0; i<10; i++){
        int x = 80 + i*50;
        xCoordinates.push_back(x);
        renderTexture(x, y , tileSize, 60);
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

void Renderer::Render(){
        SDL_RenderClear(sdlRenderer);
        SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
        renderTiles();
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