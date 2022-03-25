#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

#include "player.h"
#include "entity.h"
#include "ground.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

Player::Player(std::vector<SDL_Texture*> player_Dead, std::vector<SDL_Texture*> player_Idle, std::vector<SDL_Texture*> player_Jump, std::vector<SDL_Texture*> player_Run, std::vector<SDL_Texture*> player_Walk) {
	for (int i = 0; i < player_Dead.size(); i++) {
		player[0].push_back(PlayerStatus(player_Dead[i]));
	}
	for (int i = 0; i < player_Idle.size(); i++) {
		player[1].push_back(PlayerStatus(player_Idle[i]));
	}
	for (int i = 0; i < player_Jump.size(); i++) {
		player[2].push_back(PlayerStatus(player_Jump[i]));
	}
	for (int i = 0; i < player_Run.size(); i++) {
		player[3].push_back(PlayerStatus(player_Run[i]));
	}
	for (int i = 0; i < player_Walk.size(); i++) {
		player[4].push_back(PlayerStatus(player_Walk[i]));
	}
	status = 1;
	velocityX = 0;
	velocityY = 0;
	gravity = 0.1f;
	PLAYER_VEL = 2.5f;
	grounded = 1;
	mPosX = 0;
	mPosY = 0;
}



float Player::getWidth() {
	return player[status][0].getWidth();
}

float Player::getHeight() {
	return player[status][0].getHeight();
}
int Player::getStatus() {
	return status;
}

int Player::getLength() {
	return player[status].size();
}

PlayerStatus& Player::getTile(int p_index)
{
	return player[status].at(p_index);
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: {
			if (grounded == 1) {
				velocityY = -6.5f;
				grounded = 0;
			}
			else {
				velocityY = -6.5f;
			}
			break;
		}
					//case SDLK_DOWN: velocityY += DOT_VEL; break;
		case SDLK_LEFT: velocityX -= PLAYER_VEL; break;
		case SDLK_RIGHT: velocityX += PLAYER_VEL; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			//case SDLK_UP: velocityY += DOT_VEL; break;
			//case SDLK_DOWN: velocityY -= DOT_VEL; break;
		case SDLK_LEFT: velocityX += PLAYER_VEL; break;
		case SDLK_RIGHT: velocityX -= PLAYER_VEL; break;
		}
	}
}

bool checkCollision(Entity a, Entity b)
{
	//The sides of the rectangles
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.getX();
	rightA = a.getX() + a.getWidth();
	topA = a.getY() + 69.9f;
	bottomA = a.getY() + a.getHeight();

	//Calculate the sides of rect B
	leftB = b.getX();
	rightB = b.getX() + b.getWidth();
	topB = b.getY();
	bottomB = b.getY() + b.getHeight();
	if ((leftB + rightB) / 2.0f < leftA || rightA < (leftB + rightB) / 2.0f) {
		return false;
	}
	//If any of the sides from A are outside of B
	if (bottomA < topB)
	{
		return false;
	}

	if (topA > bottomB)
	{
		return false;
	}

	if (rightA < leftB)
	{
		return false;
	}

	if (leftA > rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void Player::update(Ground& ground)
{
	mPosX += velocityX;
	mPosY += velocityY;
	velocityY += gravity;
	bool checkX = 0, checkY = 0;
	for (int i = 0; i < ground.getLength(); i++) {
		if (ground.getStatus(i) == 3) continue;
		if (mPosX + getWidth() > SCREEN_WIDTH)
		{
			checkX = 1;
		}
		if (checkCollision(ground.getTile(i), player[status][0]))
		{
			std::cout << "i: " << i << "_status: " << ground.getStatus(i) << std::endl;
			checkY = 1;
			grounded = 1;
		}
	}
	std::cout << checkY << "______" << std::endl;
	if (checkX == 1) mPosX -= velocityX;
	if (checkY == 1) mPosY -= velocityY;

	for (int i = 0; i < getLength(); i++) {
		player[status][i].setX(mPosX);
		player[status][i].setY(mPosY);
	}
}
