#pragma once

#include <iostream>

enum class eDirection{ Stop = 0, Left = 1, UpLeft = 2, DownLeft = 3, Right = 4, UpRight = 5, DownRight = 6 };

class Ball
{
private:
	int currX, currY, startX, startY; 
	eDirection direction;
public:
	Ball(int x, int y);

	void Reset();
	void ChangeDirection(eDirection d);
	void RandomDirection();
	void Move();

	int getX() { return currX; }
	int getY() { return currY; }
	eDirection getDirection() { return direction; }

	friend std::ostream& operator<<(std::ostream& COUT, Ball ball) // For printing the current position
	{
		COUT << "Ball Position(" << ball.currX << ")(" << ball.currY << ")"
			<< "[" << (int)ball.direction << "]" << std::endl;
		return COUT;
	}
};

