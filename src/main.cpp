#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "res.h"
#include "game.h"
#include "ui.h"
#include "prng.h"

int main(int argc, char** args)
{

	prngSrand(time(NULL));
	if (!init())
	{
		printf("Failed to initialize!\n");
		SDL_Delay(100000);
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