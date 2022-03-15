#include "groundstatus.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

GroundStatus::GroundStatus(SDL_Texture* _Texture, int _index)
    : Entity{ _index * 64.0f, SCREEN_HEIGHT - 64.0f, _Texture }
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