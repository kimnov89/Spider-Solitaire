
#include<iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

class Renderer {
public:
    Renderer(const std::size_t screenWidth, const std::size_t screenHeight, const std::size_t tileSize);
    ~Renderer();
    void Render();
private:
    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
    const std::size_t screenWidth;
    const std::size_t screenHeight;
    const std::size_t tileSize;
    SDL_Texture* sdlTexture;
    void renderTiles();
    void renderTexture(int x, int y , int width, int height);
};