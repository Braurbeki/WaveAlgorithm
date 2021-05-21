#include<iostream>
#include<iomanip>
#include "Windows.h"
#include <cmath>

using namespace std;


class Labyrinth
{

private:

	static const int MAP_SIZE = 10;

	static const char wall = 'w';

	const int WALL = pow(MAP_SIZE, 2) + 2; // ��� �������� �������

	const int maxLength = pow(MAP_SIZE, 2); // ��� �������� �������

	int length = 0; // �������

	int startX = 1, startY = 1, finishX = 2, finishY = 2;

	bool WaveCalled = false;

	char map[MAP_SIZE][MAP_SIZE] =					// ������ ��������, ������������ ��� ������������, ��� w - ������
	{
		{'w', 'w', 'w', 'w','w','w','w','w','w','w'},
		{'w',' ',' ', ' ','w', ' ','w', ' ',' ','w'},
		{'w',' ',' ', ' ','w', 'w','w', 'w',' ','w'},
		{'w',' ',' ', ' ',' ', ' ',' ', 'w',' ','w'},
		{'w','w','w', 'w','w', ' ',' ', 'w',' ','w'},
		{'w',' ',' ', ' ','w', ' ',' ', ' ',' ','w'},
		{'w',' ',' ', ' ','w', 'w',' ', 'w',' ','w'},
		{'w',' ',' ', ' ','w', 'w',' ', ' ',' ','w'},
		{'w',' ',' ', ' ',' ', ' ',' ', ' ',' ','w'},
		{'w', 'w', 'w', 'w','w','w','w','w','w','w'},

	};

	int coords[MAP_SIZE][MAP_SIZE]; // ��� ������� ������

	void FillCoords() //��������� ������� ������, � ����������� �� �����
	{
		for (int y = 0; y < MAP_SIZE; y++)
		{
			for (int x = 0; x < MAP_SIZE; x++)
			{
				if (map[y][x] == wall) { coords[y][x] = WALL; } // ����� - 102

				else if (map[y][x] == ' ') { coords[y][x] = pow(MAP_SIZE, 2) + 1; } //��������� ������ - 101

				else if (map[y][x] == 'f') coords[y][x] = 0; // ����� 0

				else if (map[y][x] == 's') coords[y][x] = pow(MAP_SIZE, 2); //����� - 100
			}
		}
	}

	void moveWave() //����������� ������� �������������� �����, ��������                   ����������� �� ��� ���, 
	{				//���� �� ��������� ���������(101) �������� � ������� �������,
					//��� ������� �� ��������� ������ ������������� ��������

		for (int y = 0; y < MAP_SIZE; y++)
		{
			for (int x = 0; x < MAP_SIZE; x++)
			{
				if (length > maxLength) { return; }
				if (coords[y][x] == length)		//�������� ������ ���������������, ��� ����������� ��� �������(4 �������� ����:
				{								//�����, ����, ������, �����)
					if (coords[y][x + 1] == WALL) { goto second; }
					else createPath(x + 1, y);

				second: if (coords[y][x - 1] == WALL) { goto third; }
				else createPath(x - 1, y);

			third: if (coords[y + 1][x] == WALL) { goto fourth; }
			else createPath(x, y + 1);

		fourth: if (coords[y - 1][x] == WALL) { continue; }
		else { createPath(x, y - 1); }
				}
			}
		}
		length++;
		moveWave();

	}

	void createPath(int x, int y) // ����������� �������� �������� �������� + 1
	{
		if (coords[y][x] == pow(MAP_SIZE, 2) + 1) coords[y][x] = length + 1;
	}



	void findPath(int x, int y)//����������� ������� ������ ����������� ����
	{
		int minY = min(coords[y + 1][x], coords[y - 1][x]), minX = min(coords[y][x + 1], coords[y][x - 1]);
		int minVal = min(minY, minX); //����� �������� ������ � ���������� ���������


		for (; y < MAP_SIZE; y++)
		{
			for (; x < MAP_SIZE; x++)
			{
				if (length > maxLength) //���� ���������� ��������� �� ������, �������� �����������
				{
					map[startY][startX] = 's';
					cout << "Can't find path\n";
					return;
				}

				if (coords[y + 1][x] == minVal) { y++; goto rec; }

				else if (coords[y - 1][x] == minVal) { y--; goto rec; }

				else if (coords[y][x + 1] == minVal) { x++; goto rec; }

				else if (coords[y][x - 1] == minVal) { x--; goto rec; }

			}

		}
	rec:
		if (coords[y][x] != 0)
		{
			length++;
			map[y][x] = 'p'; // �������������� ������������ ����
			findPath(x, y);

		}

	}



	void FillGaps() // ��������� �� ���������� ������ ��������� ������ ���������
	{
		for (int y = 0; y < MAP_SIZE; y++)
		{
			for (int x = 0; x < MAP_SIZE; x++)
			{
				if (coords[y][x] == pow(MAP_SIZE, 2) + 1)
				{
					map[y][x] = '-';
				}
			}
		}
	}




public:

	void Wave()
	{
		WaveCalled = true;

		FillCoords();

		moveWave();

		length = 0; // nullify counter for findPath 

		findPath(startX, startY);

		FillGaps();

	}

	void setStartPoint(int x, int y)
	{
		if (y > MAP_SIZE || x > MAP_SIZE || y < 0 || x < 0)
		{
			cout << "x/y must be <= 10\n";
			return;
		}
		else if (map[y][x] != 'w')
		{
			map[startY][startX] = ' ';
			startX = x;
			startY = y;
			map[startY][startX] = 's';
		}
		else
		{
			cout << "You can't put start point on the wall\n";
		}


	}


	void setFinishPoint(int x, int y)
	{
		if (y > MAP_SIZE || x > MAP_SIZE || y < 0 || x < 0)
		{
			cout << "x/y must be <= 10\n";
			return;
		}
		else if (map[y][x] != 'w')
		{
			map[finishY][finishX] = ' ';
			finishX = x;
			finishY = y;
			map[finishY][finishX] = 'f';
		}
		else
		{
			cout << "You can't put finish point on the wall\n";
			return;
		}


	}


	void printMatrix() //������� ������ �������
	{
		if (!WaveCalled)
		{
			cout << "Wave function wasn't called. Matrix can't be printed";
			return;
		}

		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //WHITE 
		cout << "y/x\n"; cout << " "; for (int j = 0; j < MAP_SIZE; j++) { cout << setw(3) << j; }
		cout << endl;
		for (int i = 0; i < MAP_SIZE; i++)
		{
			cout << i;
			for (int j = 0; j < MAP_SIZE; j++)
			{
				switch (map[i][j])
				{
				case wall:
					SetConsoleTextAttribute(handle, FOREGROUND_RED);
					cout << setw(3) << "w";
					break;
				case 's': // start 
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE); //CYAN 
					cout << setw(3) << "s";
					break;
				case 'p': // path 
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE); //MAGENTA
					cout << setw(3) << coords[i][j];
					break;
				case 'f': // finish
					SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
					cout << setw(3) << "f";
					break;
				case '-':
					cout << setw(3) << " ";
					break;
				default:
					SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
					cout << setw(3) << coords[i][j];
					break;
				}

			}
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //WHITE
			cout << endl;
		}
	}
};
