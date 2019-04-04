#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	srand(time(NULL));
	fruitX = 2 + (rand() % (width - 3));
	fruitY = 2 + (rand() % (height - 3));
	score = 0;
	nTail = 0;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width; ++i)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 1; i < height - 1; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "#";
			}
			else if (i == y && j == x)
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; ++k)
				{
					if (i == tailY[k] && j == tailX[k])
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width; ++i)
	{
		cout << "#";
	}
	cout << endl << endl << "Score: " << score << endl << endl;
	cout << "Controls:" << endl << "wasd - movements" << endl << "x - exit the game" << endl << endl;
}
void Input()
{
	if (_kbhit())
	{
		auto new_dir = _getch();
		switch (new_dir)
		{
		case 'a':
			if (dir != RIGHT)
			{
				dir = LEFT;
			}
			break;
		case 'd':
			if (dir != LEFT)
			{
				dir = RIGHT;
			}
			break;
		case 'w':
			if (dir != DOWN)
			{
				dir = UP;
			}
			break;
		case 's':
			if (dir != UP)
			{
				dir = DOWN;
			}
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prevXtemp, prevYtemp;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; ++i)
	{
		prevXtemp = tailX[i];
		prevYtemp = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prevXtemp;
		prevY = prevYtemp;
	}

	switch (dir)
	{
	case LEFT:
		--x;
		break;
	case RIGHT:
		++x;
		break;
	case UP:
		--y;
		break;
	case DOWN:
		++y;
		break;
	default:
		break;
	}

	/*if (x >= width || x <= 0 || y >= height || y <= 0)
	{
	gameOver = true;
	}*/
	if (x >= width)
	{
		x = 1;
	}
	else if (x <= 0)
	{
		x = width - 2;
	}
	if (y >= height)
	{
		y = 1;
	}
	else if (y <= 0)
	{
		y = height - 2;
	}
	for (int i = 0; i < nTail; ++i)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY)
	{
		nTail++;
		score += 10;
		fruitX = 2 + (rand() % (width - 3));
		fruitY = 2 + (rand() % (height - 3));
	}
}

int main(int argc, char *argv[])
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}

	return 0;
}
