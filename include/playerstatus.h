#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "entity.h"

class PlayerStatus
: public Entity
{
public:
	PlayerStatus(SDL_Texture* _Texture);
	int getStatus();
	void setStatus(int p_status, SDL_Texture* groundTex[4]);
private:
	int status;
};