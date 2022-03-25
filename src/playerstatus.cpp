#include "playerstatus.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;


PlayerStatus::PlayerStatus(SDL_Texture* _Texture)
    : Entity{ 0.0f,  0.0f, _Texture }
{
    status = 1;
}

int PlayerStatus::getStatus()
{
    return status;
}
