#include "game.h"

bool Game::game_running = false; 
int Game::width = 0; 
int Game::height = 0;
char Game::p1_up = 'w'; 
char Game::p1_down = 's';
char Game::p2_up = 'i';
char Game::p2_down = 'k';
Ball* Game::ball = nullptr; 
Player* Game::player1 = nullptr;
int Game::p1_score = 0;
Player* Game::player2 = nullptr;
int Game::p2_score = 0;

void Game::Start(int w, int h)
{
	std::string p_names = "";
	srand(time(nullptr));

	width = w;
	height = h;

	ball = new Ball(w / 2, h / 2); // Ball placed in the middle

	DisplayColoredText("Enter the first players name:", Color::Cyan);
	std::cin >> p_names;
	player1 = new Player(1, h / 2 - 3, p_names); // Placed to eh left of the window
	DisplayColoredText("Enter the second players name:", Color::Cyan);
	std::cin >> p_names;
	player2 = new Player(w - 2, h / 2 - 3, p_names); // Placed to eh right of the window
	game_running = true;

	while (game_running)
	{
		Game::DrawMap();
		Game::Frame();
		Game::Colision();
		Sleep(60);
	}
}

void Game::DrawMap()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		std::cout << "\xB2";
	std::cout << std::endl;

	for (int i = 0; i < height; i++)
	{ 
		for (int j = 0; j < width; j++)
		{
			if (j == 0) std::cout << "\xB2";

			if (ball->getX() == j && ball->getY() == i) std::cout << "O"; // ball
			else if (player1->getX() == j && player1->getY() == i) std::cout << "\xDB"; // player1
			else if (player1->getX() == j && player1->getY() + 1 == i) std::cout << "\xDB"; // player1
			else if (player1->getX() == j && player1->getY() + 2 == i) std::cout << "\xDB"; // player1
			else if (player1->getX() == j && player1->getY() + 3 == i) std::cout << "\xDB"; // player1

			else if (player2->getX() == j && player2->getY() == i) std::cout << "\xDB"; // player2
			else if (player2->getX() == j && player2->getY() + 1 == i) std::cout << "\xDB"; // player2
			else if (player2->getX() == j && player2->getY() + 2 == i) std::cout << "\xDB"; // player2
			else if (player2->getX() == j && player2->getY() + 3 == i) std::cout << "\xDB"; // player2
			else std::cout << " ";

			if (j == width - 1) std::cout << "\xB2";
		}
		std::cout << std::endl;
	}
	
	for (int i = 0; i < width + 2; i++)
		std::cout << "\xB2";
	std::cout << std::endl;

	std::cout << "Score:" << std::endl;
	DisplayColoredText(player1->getName(), Color::Cyan);
	std::cout << " : ";
	DisplayColoredText(p1_score, Color::Green);
	std::cout << std::endl;
	DisplayColoredText(player2->getName(), Color::Magenta);
	std::cout << " : ";
	DisplayColoredText(p2_score, Color::Green);
}

void Game::Frame()
{
	ball->Move();

	if (_kbhit())
	{
		char pressed = _getch();
		// Player 1
		if (pressed == p1_up)
			if (player1->getY() + 4 == height - 1) player1->Stop();
			else if(player1->getY() + 4 > 0) player1->MoveUp();
			else player1->Stop();
		if (pressed == p1_down)
			if (player1->getY() + 4 == 5)	player1->Stop();
			else if (player1->getY() + 4 < height) player1->MoveDown();
			else player1->Stop();

		// Player 2
		if (pressed == p2_up)
			if (player2->getY() + 4 == height - 1)	player2->Stop();
			else if (player2->getY() + 4 > 0)	player2->MoveUp();
			else player2->Stop();
		if (pressed == p2_down)
			if (player2->getY() + 4 == 5) player2->Stop();
			else if (player2->getY() + 4 < height) player2->MoveDown();
			else player2->Stop();

		// Ball
		if (ball->getDirection() == eDirection::Stop) 
			ball->RandomDirection();

		if (pressed == 'q') game_running = false;
	}
}

void Game::Colision()
{
	// Player 1
	for (int i = 0; i < 4; i++)
	{
		if (ball->getX() == player1->getX() + 1)
			if(ball->getY() == player1->getY() + i) 
				ball->ChangeDirection((eDirection)((rand() % 3) + 4));
	}

	// Player 2
	for (int i = 0; i < 4; i++)
	{
		if (ball->getX() == player2->getX() - 1)
			if (ball->getY() == player2->getY() + i)
				ball->ChangeDirection((eDirection)((rand() % 3) + 1));
	}

	// Bottom Wall
	if (ball->getY() == height - 1)
		ball->ChangeDirection(ball->getDirection() == eDirection::DownRight ? eDirection::UpRight : eDirection::UpLeft);
		
	// Top Wall
	if (ball->getY() == 0)
		ball->ChangeDirection(ball->getDirection() == eDirection::UpRight ? eDirection::DownRight : eDirection::DownLeft);

	// Right Wall
	if (ball->getX() == width - 1)
		Game::Score(player1, ball);

	// Left Wall
	if (ball->getX() == 0)
		Game::Score(player2, ball);
}

void Game::Score(Player* other_player, Ball* ball)
{
	if (other_player == player1) p1_score++;
	else p2_score++; 
	Game::Reset();
}

void Game::Reset()
{
	ball->Reset();
	player1->Reset();
	player2->Reset();
}

void Game::End()
{
	delete ball, player1, player2;
}

void DisplayColoredText(const std::string& text, Color color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
	std::cout << text ;
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(Color::White));
}

void DisplayColoredText(const int& number, Color color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
	std::cout << number;
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(Color::White));
}
