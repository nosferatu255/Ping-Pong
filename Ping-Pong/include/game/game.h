#pragma once

#include <time.h>
#include <conio.h>
#include <Windows.h>

#include "ball.h"
#include "player.h"

enum class Color
{
	Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	Cyan = FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
	Magenta = FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
};

void DisplayColoredText(const std::string& text, Color color);
void DisplayColoredText(const int& number, Color color);

class Game
{
private:
	static int height, width;
	static char p1_up, p1_down, p2_up, p2_down;
	static Ball* ball;
	static Player* player1;
	static int p1_score;
	static Player* player2;
	static int p2_score;
	static bool game_running;
public:
	static void Start(int w, int h);
	static void DrawMap();
	static void Frame();
	static void Colision();
	static void Score(Player* other_player, Ball* ball);
	static void Reset();
	static void End();
};