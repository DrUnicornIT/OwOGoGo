#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "ground.h"
#include "groundstatus.h"


Ground::Ground(SDL_Texture* left, SDL_Texture* center, SDL_Texture* right, SDL_Texture* hole)
{
    groundTexture[0] = left;
    groundTexture[1] = center;
    groundTexture[2] = right;
    groundTexture[3] = hole;

    for (int i = 0; i < 14; i++)
    {
        groundTiles.push_back(GroundStatus(groundTexture[1], i));
    }
}

GroundStatus& Ground::getTile(int p_index)
{
    return groundTiles.at(p_index);
}

int Ground::getStatus(int p_index)
{
    return groundTiles[p_index].getStatus();
}

int Ground::getLength()
{
    return groundTiles.size();
}

void Ground::reset()
{
    for (int i = 0; i < 14; i++)
    {
        groundTiles[i].setStatus(1, groundTexture);
        groundTiles[i].setX(i * 64.0f);
    }
    lastStatus = 1;
    holeCount = 0;
}

void Ground::update(int score)
{
    for (int i = 0; i < getLength(); i++)
    {
        groundTiles[i].setX(groundTiles[i].getX() - 1);
        if (groundTiles[i].getX() + 64 < 0)
        {
            groundTiles[i].setX(64 * (getLength() - 1) - 1);
            switch (lastStatus)
            {
            case 0:
            {
                groundTiles[i].setStatus(1, groundTexture);
                lastStatus = 1;
                holeCount = 0;
                break;
            }
            case 1:
            {
                int randomInt = rand() % 2 + 1;
                groundTiles[i].setStatus(randomInt, groundTexture);
                lastStatus = randomInt;
                holeCount = 0;
                break;
            }
            case 2:
            {
                groundTiles[i].setStatus(3, groundTexture);
                lastStatus = 3;
                holeCount = 0;
                break;
            }
            case 3:
            {
                int randomInt = rand() % 2;
                if (randomInt == 1)
                {
                    randomInt = 3;
                    holeCount++;
                }
                else
                {
                    holeCount = 0;
                }
                if ((holeCount > 4 && score > 99) || (holeCount > 3 && score < 100))
                {
                    randomInt = 0;
                    holeCount = 0;
                }
                groundTiles[i].setStatus(randomInt, groundTexture);
                lastStatus = randomInt;
                break;
            }
            }
        }
        // cout << "___" << groundTiles[i].getStatus() << endl;
    }
    // cout << "Done___" << endl;
}