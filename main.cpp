#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <process.h>

using namespace std;
fstream highscore;
bool gameOver;
const int width = 21;
const int height = 21;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
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
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
	if (tailX[i] == x && tailY[i] == y)
		gameOver = true;
	if (x == fruitX && y == fruitY)
	{
		score += 1;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	int choice;
	char ch,name[100],day[100],info[300];
	do{
        score = 0;
		system("cls");
		cout << "Welcome to the Snake Game!" << endl;
		cout << "1. Rookie" << endl;
		cout << "2. Intermediate" << endl;
		cout << "3. Expert" << endl;
		/*cout << "4. Highscores" << endl;*/
		cout << "\n\n Select your choice: ";
		cin >> choice;
		switch (choice)
		{

		case 1:
		{
				  Setup();
				  while (!gameOver)
				  {
					  Draw();
					  Input();
					  Logic();
					  Sleep(30);
				  }
				  break;
		}
		case 2:
		{
				  Setup();
				  while (!gameOver)
				  {
					  Draw();
					  Input();
					  Logic();
					  Sleep(10);
				  }
				  break;
		}
		case 3:
		{
				  Setup();
				  while (!gameOver)
				  {
					  Draw();
					  Input();
					  Logic();
				  }
				  break;
		}
		/*case 4:
		{
				  highscore.open("leaderboard.txt", ios::out);
				  while (!highscore.eof())
				  {
					  highscore >> info;
					  cout << info << endl;
				  }
				  highscore.close();
				  break;
		}*/
		}
		system("cls");
		cout << "\n\n\n\n\nYour score was: " << score << endl;
		/*cout << "Enter your name: ";
		cin >> name;
		cout << "Enter the date (day/month/year): ";
		cin >> day;
		highscore.open("leaderboard.txt", ios::in | ios::app);
		while (!highscore.eof())
		{
			highscore << name << ", "<< score << ", "<< day;
		}
		highscore.close();
		system("cls");
		*/
		cout << "Do you want to play again? (y/n)" << endl;
		cin >> ch;
	} while(ch == 'y' || ch == 'Y');
	return 0;
}
