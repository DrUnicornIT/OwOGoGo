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
const float LimitUp = SCREEN_HEIGHT - 650.0f;

Ground::Ground(SDL_Texture* _short, SDL_Texture* _medium, SDL_Texture* _long, SDL_Texture* hole)
{
    groundTexture[0] = _short;
    groundTexture[1] = _medium;
    groundTexture[2] = _long;
    groundTexture[3] = hole;
    float start_x = 0;
    int nonHole = 0;
    int numHoles = 0;
    bool statusPre = 0;
    for (int i = 0; i < LEN; i++)
    {
        if (statusPre) {
            groundTiles.push_back(GroundStatus(groundTexture[3], start_x, randFloat(LimitBottom, LimitUp)));
            start_x += groundTiles[i].getWidth();
            std::cout << "start_x: " << start_x << '\n';
            numHoles++;
            statusPre = 0;
            continue;
        }
        groundTiles.push_back(GroundStatus(groundTexture[randInt(0, 3 - nonHole)], start_x, randFloat(LimitBottom, LimitUp)));
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
        std::cout << "start_x: " << start_x << '\n';
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

void Ground::update(int score, float& newHeghtGround, float& gravity)
{
    for (int i = 0; i < getLength(); i++) {
        groundTiles[i].setX(groundTiles[i].getX() - 3.5f);
        std::cout << "groundTiles[i].getX(): " << groundTiles[i].getX() << '\n';
        if (groundTiles[i].getY() == SCREEN_HEIGHT)
            groundTiles[i].setY(randFloat(LimitBottom, LimitUp));

        if (groundTiles[i].getX() + groundTiles[i].getWidth() < 0) {
            // std::cout << "." << '\n';
            groundTiles[i].setX(groundTiles[previous(i)].getX() + groundTiles[previous(i)].getWidth());
            // std::cout << "new X" << previous(i) << " " << groundTiles[previous(i)].getX() << " " << groundTiles[i].getX() << '\n';
            groundTiles[i].setY(SCREEN_HEIGHT);
        }
    }
}