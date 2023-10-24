#include "player.h"

Player::Player(int x, int y, std::string n)
{
	startX = x;
	startY = y;

	currX = x; 
	currY = y;

	name = n;
}

void Player::Reset()
{
	currX = startX;
	currY = startY;
}

