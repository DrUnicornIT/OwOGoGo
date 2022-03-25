#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

#include "entity.h"
#include "ground.h"
#include "PlayerStatus.h"

class Player {
public:
    Player(std::vector<SDL_Texture*> player_Dead,
        std::vector<SDL_Texture*> player_Idle,
        std::vector<SDL_Texture*> player_Jump,
        std::vector<SDL_Texture*> player_Run,
        std::vector<SDL_Texture*> player_Walk);
    void handleEvent( SDL_Event& e );
    void update(Ground& ground);
    float getWidth();
    float getHeight();
    int getLength();
    int getStatus();
    float distanceFromCursor();
    bool jump();
    PlayerStatus& getTile(int p_index);
private:
    float velocityX, velocityY;
    std::vector<PlayerStatus> player[5];
    int status;
    bool grounded;
    float PLAYER_VEL;
    float gravity;
    float mPosX, mPosY;
};