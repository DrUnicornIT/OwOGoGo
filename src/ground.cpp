#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ground.h"
#include "groundstatus.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

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

void Ground::update(int score, float& newHeghtGround, float& gravity)
{
    for (int i = 0; i < getLength(); i++)
    {
        groundTiles[i].setX(groundTiles[i].getX() - 2);
        groundTiles[i].setY(groundTiles[i].getY() + gravity);
        // printf("%d\n", i);

        if (groundTiles[i].getX() + 64 < 0)
        {
            groundTiles[i].setX(64 * (getLength() - 1) - 1);
            printf("%f\n", newHeghtGround);
            groundTiles[i].setY(newHeghtGround);
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
                newHeghtGround -= 1.11f;
                printf("Nang cao");
                printf("%f\n", newHeghtGround);
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
                if ((holeCount > 3 && score > 99) || (holeCount > 2 && score < 100))
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
    for (int i = 1; i < getLength(); i++) {
        if (((getStatus(i - 1) == 0 && getStatus(i) == 1) || (getStatus(i - 1) == 1 && getStatus(i) == 1) || (getStatus(i - 1) == 1 && getStatus(i) == 2)) && groundTiles[i].getX() > groundTiles[i - 1].getX()) {
            groundTiles[i].setY(groundTiles[i - 1].getY());
            newHeghtGround = std::min(newHeghtGround, groundTiles[i].getY());
            std::cout << i << " " << groundTiles[i].getY() << '\n';
        }
    }
    if (((getStatus(getLength() - 1) == 0 && getStatus(0) == 1) || (getStatus(getLength() - 1) == 1 && getStatus(0) == 1) || (getStatus(getLength() - 1) == 1 && getStatus(0) == 2)) && groundTiles[0].getX() > groundTiles[getLength() - 1].getX()) {
        groundTiles[0].setY(groundTiles[getLength() - 1].getY());
        newHeghtGround = std::min(newHeghtGround, groundTiles[0].getY());
        std::cout << 0 << " " << groundTiles[0].getY() << '\n';
    }
    if (newHeghtGround < SCREEN_HEIGHT - 128.0f)
    {
        gravity = 0.15f;
    }
    else {
        gravity = 0.1f;
    }
    // cout << "Done___" << endl;
}