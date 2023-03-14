
#include<iostream>
#include <string>
#include <vector>
#include <map>
#include "SDL.h"
#include "SDL_image.h"
#include "Card.h"


class Renderer {
public:
    Renderer(const std::size_t screenWidth, const std::size_t screenHeight);
    ~Renderer();
    void Render(const std::vector<std::vector<Card>> &CardStacks, const std::vector<Card> &CardDrawStack, int rowCount);
    void LoadTexture(std::string path);
private:
    SDL_Window* sdlWindow;//freed in destructor
    SDL_Renderer* sdlRenderer;//freed in destructor
    const std::size_t screenWidth;
    const std::size_t screenHeight;
    SDL_Texture* sdlTexture;//freed in function
    void renderTexture(int x, int y , int width, int height);
    std::map<int, std::string> cardDeck;
    std::vector<std::map<int, std::string>> cardPool;
};