#pragma once

#include <iostream>

class Player
{
private:
	int currX, currY, startX, startY;
	std::string name;
public:
	Player(int x, int y, std::string n);

	void Reset();
	void MoveDown() { currY--; }
	void MoveUp() { currY++; }
	void Stop() { currY = currY; }

	int getX() { return currX; }
	int getY() { return currY; }
	std::string getName() { return name; }

	friend std::ostream& operator<<(std::ostream& COUT, Player player) // For printing the current position
	{
		COUT << "Player Position(" << player.currX << ")(" << player.currY << ")" << std::endl;
		return COUT;
	}
};

