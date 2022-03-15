#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <stdlib.h>

#include "renderwindow.h"
#include "ground.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
bool runGame();

RenderWindow window;
SDL_Texture* groundTexture[4];

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



bool loadMedia()
{
	bool success = true;
	window.create("OwOGoGo", SCREEN_WIDTH, SCREEN_HEIGHT);

	groundTexture[0] = window.loadTexture("img/left.png");
	if (groundTexture[0] == NULL) {
		printf("Failed to load left texture!\n");
		success = false;
	}
	groundTexture[1] = window.loadTexture("img/center.png");
	groundTexture[2] = window.loadTexture("img/right.png");
	groundTexture[3] = window.loadTexture("img/hole.png");
	return success;
}

bool Load = loadMedia();

Ground ground(groundTexture[0], groundTexture[1], groundTexture[2], groundTexture[3]);

bool runGame()
{
	bool success = true;

	SDL_Event event;
	bool quit = false;
	float newHeghtGround = SCREEN_HEIGHT - 350.0f;
	float gravity = 0.0f;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT: {
				quit = true;
				break;
			}
			}
		}
		ground.update(50, newHeghtGround, gravity);
		window.clear();
		/// 0 easy, 50 normal, 100 hard

		for (int i = 0; i < ground.getLength(); i++)
		{
			window.render(ground.getTile(i));
		}
		window.display();
		SDL_Delay(16);
	}
	return success;
}

int main(int argc, char* args[])
{

	std::cout << "Start running game.\n";
	if (init()) {
		std::cout << "Game init success.\n";
		if (Load) {
			std::cout << "Game load media success.\n";
			if (runGame()) {
				std::cout << "Game run success.\n";
			}
			else {
				std::cout << "Game run failed.\n";
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