#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <stdlib.h>

#include "player.h"
#include "entity.h"
#include "renderwindow.h"
#include "ground.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;


bool init();
bool loadMedia();
bool runGame();

RenderWindow window;
SDL_Texture* groundTexture[4];
std::vector<SDL_Texture*> player_Dead;
std::vector<SDL_Texture*> player_Idle;
std::vector<SDL_Texture*> player_Jump;
std::vector<SDL_Texture*> player_Run;
std::vector<SDL_Texture*> player_Walk;
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

	groundTexture[0] = window.loadTexture("img/short.png");
	groundTexture[1] = window.loadTexture("img/medium.png");
	groundTexture[2] = window.loadTexture("img/long.png");
	groundTexture[3] = window.loadTexture("img/hole.png");
	for (int i = 1; i <= 30; i++) {
		player_Dead.push_back(window.loadTexture("img/player/female/Dead (" + std::to_string(i) + ").png"));
	}

	for (int i = 1; i <= 16; i++) {
		player_Idle.push_back(window.loadTexture("img/player/female/Idle (" + std::to_string(i) + ").png"));
	}

	for (int i = 1; i <= 30; i++) {
		player_Jump.push_back(window.loadTexture("img/player/female/Jump (" + std::to_string(i) + ").png"));
	}

	for (int i = 1; i <= 20; i++) {
		player_Run.push_back(window.loadTexture("img/player/female/Run (" + std::to_string(i) + ").png"));
	}

	for (int i = 1; i <= 20; i++) {
		player_Walk.push_back(window.loadTexture("img/player/female/Walk (" + std::to_string(i) + ").png"));
	}
	SDL_Delay(1000);
	return success;
}

bool Load = loadMedia();

Player player_Female(player_Dead, player_Idle, player_Jump, player_Run, player_Walk);
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
			player_Female.handleEvent(event);
		}
		ground.update(50, newHeghtGround, gravity);
		player_Female.update(ground);
		window.clear();
		/// 0 easy, 50 normal, 100 hard

		for (int i = 0; i < ground.getLength(); i++) {
			window.render(ground.getTile(i));
		}
		for (int i = 0; i < player_Female.getLength(); i++) {
			window.render(player_Female.getTile(i));
		}
		window.display();
		SDL_Delay(16);
	}
	return success;
}

int main(int argc, char* args[])
{
	srand((unsigned)time(0));
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