#include "ball.h"

Ball::Ball(int x, int y)
{
	startX = x;
	startY = y;
	currX = x;
	currY = y;
	direction = eDirection::Stop;
}

void Ball::Reset()
{
	currX = startX;
	currY = startY;
	direction = eDirection::Stop;
}

void Ball::ChangeDirection(eDirection d)
{
	direction = d;
}

void Ball::RandomDirection()
{
	direction = (eDirection)((rand() % 6) + 1); // Generates a random number between 1 and 6
}

void Ball::Move()
{
	switch (direction)
	{
	case eDirection::Stop:
		break;
	case eDirection::Left:
		currX--; break;
	case eDirection::UpLeft:
		currX--; currY--; break;
	case eDirection::DownLeft:
		currX--; currY++; break;
	case eDirection::Right:
		currX++; break;
	case eDirection::UpRight:
		currX++; currY--; break;
	case eDirection::DownRight:
		currX++; currY++; break;
	default:
		break;
	}
}

