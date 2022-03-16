#include "groundstatus.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;


GroundStatus::GroundStatus(SDL_Texture* _Texture, int _x, int _y)
    : Entity{ _x,  _y, _Texture }
{
    status = 1;
}

int GroundStatus::getStatus()
{
    return status;
}

void GroundStatus::setStatus(int _status, SDL_Texture* groundTex[4])
{
    status = _status;
    setTex(groundTex[status]);
}