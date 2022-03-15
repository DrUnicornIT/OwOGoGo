#pragma once 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "groundstatus.h"

class Ground {
public:
    Ground(SDL_Texture* left, SDL_Texture* center, SDL_Texture* right, SDL_Texture* hole);
    GroundStatus& getTile(int p_index);
    int getStatus(int p_index);
    int getLength();
    bool isTileBelow(float x, int width);
    void update(int score);
    void reset();
private:
    std::vector<GroundStatus> groundTiles;
    SDL_Texture* groundTexture[4];
    int lastStatus = 1;
    int holeCount = 0;
};