#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ground.h"
#include "groundstatus.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const int LEN = 14;

int randInt(int l, int r) {
    return rand() % (r - l + 1) + l;
}

int previous(int i) {
    if (i == 0) {
        return LEN - 1;
    }
    return i - 1;
}

float randFloat(float L, float R) {
    return (R - L) * ((float)rand() / (float)RAND_MAX) + L;
}

const float LimitBottom = SCREEN_HEIGHT - 250.0f;
const float LimitUp = SCREEN_HEIGHT - 600.0f;

Ground::Ground(SDL_Texture* _short, SDL_Texture* _medium, SDL_Texture* _long, SDL_Texture* hole)
{

    groundTexture[0] = _short;
    groundTexture[1] = _medium;
    groundTexture[2] = _long;
    groundTexture[3] = hole;
    float start_x = 0;
    int nonHole = 0;
    int numHoles = 0;
    bool statusPre = 1;
    groundTiles.push_back(GroundStatus(groundTexture[2], start_x, LimitBottom));
    groundTiles[0].setStatus(2, groundTexture);
    start_x += groundTiles[0].getWidth();
    for (int i = 1; i < LEN; i++)
    {
        if (statusPre) {
            groundTiles.push_back(GroundStatus(groundTexture[3], start_x, randFloat(LimitBottom, LimitUp)));
            groundTiles[0].setStatus(3, groundTexture);
            start_x += groundTiles[i].getWidth();
            numHoles++;
            statusPre = 0;
            if (numHoles == 2) {
                nonHole = 1;
            }
            else {
                nonHole = 0;
            }
            continue;
        }
        int randII = randInt(0, 3 - nonHole);
        groundTiles.push_back(GroundStatus(groundTexture[randII], start_x, randFloat(LimitBottom, LimitUp)));
        groundTiles[0].setStatus(2, groundTexture);
        if (groundTiles[i].getStatus() == 3) {
            numHoles++;
            statusPre = 0;
        }
        else {
            numHoles = 0;
            statusPre = 1;
        }
        if (numHoles == 2) {
            nonHole = 1;
        }
        else {
            nonHole = 0;
        }
        start_x += groundTiles[i].getWidth();
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

bool Ground::isTileBelow(float x, int width)
{
    for (int i = 0; i < getLength(); i++)
    {
        switch (getStatus(i)) {
        case 0:
            if (x + width > groundTiles[i].getX() + 24 && x < groundTiles[i].getX() + 64)
            {
                return true;
            }
            break;
        case 1:
            if (x + width > groundTiles[i].getX() && x < groundTiles[i].getX() + 64)
            {
                return true;
            }
            break;
        case 2:
            if (x + width > groundTiles[i].getX() && x < groundTiles[i].getX() + 40)
            {
                return true;
            }
            break;
        }
    }
    return false;
}

void Ground::update(int score, float& newHeghtGround, float& gravity)
{

    for (int i = 0; i < getLength(); i++) {
        /// - 3.5f
        groundTiles[i].setX(groundTiles[i].getX() - 3.5);
        if (groundTiles[i].getY() == SCREEN_HEIGHT)
            groundTiles[i].setY(randFloat(LimitBottom, LimitUp));

        if (groundTiles[i].getX() + groundTiles[i].getWidth() < 0) {
            groundTiles[i].setX(groundTiles[previous(i)].getX() + groundTiles[previous(i)].getWidth());
            groundTiles[i].setY(SCREEN_HEIGHT);
        }
        
    }
}