#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "entity.h"

class GroundStatus
: public Entity
{
public:
	GroundStatus(SDL_Texture* _Texture, int _x, int _y);
	int getStatus();
	void setStatus(int p_status, SDL_Texture* groundTex[4]);
private:
	int status;
};