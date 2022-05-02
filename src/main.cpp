<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "res.h"
#include "game.h"
#include "ui.h"
#include "prng.h"

int main(int argc, char **args)
{
  prngSrand(time(NULL));
  if (!init())
  {
    printf("Failed to initialize!\n");
  }
  else
  {
    // Load media
    if (!loadMedia())
    {
      printf("Failed to load media!\n");
    }
    else
    {
      mainUi();
    }
  }
  cleanup();
}
=======
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include "CommonFunction.h"
#include "renderwindow.h"
#include "resourceHandler.h"
#include "Game.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;


bool init();
bool loadMedia();
bool runGame();


bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}

		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
	}
	return success;
}


ResHandler resourceHandler;
Game game;
bool loadMedia()
{
	bool success = true;
	window.create("OwOGoGo", SCREEN_WIDTH, SCREEN_HEIGHT);
	resourceHandler.load();
	std::cout << "Loadmedia done.";
	SDL_Delay(100);
	return success;
}

bool Load = loadMedia();

int main(int argc, char* args[])
{
	srand((unsigned)time(0));
	/// seed random number generator
	std::cout << "Start running game.\n";
	if (init()) {
		std::cout << "Game init success.\n";
		if (Load) {
			std::cout << "Game load media success.\n";
			if (game.RunGame()) {
				std::cout << "Game runned success.\n";
			}
			else {
				std::cout << "Game runned failed.\n";
			}
		}
		else {
			std::cout << "Game load media failed.\n";
		}
	}
	else {
		std::cout << "Game init failed.\n";
	}
	return 0;
}
>>>>>>> dc059530e34e9b213858f7658c53a8821b76204a
