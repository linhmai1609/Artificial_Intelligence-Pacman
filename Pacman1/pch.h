// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#include<iostream>
#include<list>
#include<fstream>
#include<Windows.h>
#include<cstring>
#include <algorithm>  
#include <vector>
#include <ctime>

using namespace std;

// TODO: add headers that you want to pre-compile here
const int MAP_HEIGHT = 22;
const int MAP_WIDTH = 22;
const int DEFAULT_POINT = 0;

//ASCII 
const int TOPLEFT = 201;
const int TOPRIGHT = 187;
const int BOTLEFT = 200;
const int BOTRIGHT = 188;
const int UP_EDGE = 186;
const int DOWN_EDGE = 205;
const int WALL = 219;
const int PACMAN = 228;
const int GHOST = 234;
const int GO = 46;
const int FOOD = 248;

void ClearScreen();

class Position {
private:
	int positionX;
	int positionY;
	int parentX;
	int parentY;
public:
	int getX() {
		return positionX;
	}
	int getY() {
		return positionY;
	}
	Position(int x, int y) {
		positionX = x;
		positionY = y;
	}
	void setParent(int x, int y) {
		parentX = x;
		parentY = y;
	}
	int getPX() {
		return parentX;
	}
	int getPY() {
		return parentY;
	}
	Position() {};
};

class Map {
private:
	int mapIndexes[MAP_HEIGHT][MAP_WIDTH];
	char mapGraphics[MAP_HEIGHT][MAP_WIDTH];
	int level;
public:
	Position foodPosition;
	Map() {
		for (int i = 0; i < MAP_WIDTH; i++)
			for (int j = 0; j < MAP_HEIGHT; j++)
				mapIndexes[i][j] = 0;

		for (int i = 0; i < MAP_WIDTH; i++)
			for (int j = 0; j < MAP_HEIGHT; j++)
				mapGraphics[i][j] = char(32);
		level = 0;
		foodPosition = Position(0, 0);
	};
	void setMap(ifstream f);
	void setAttr(int x, int y, int attr);
	int getPosition(int x, int y);
	void InitGraphic();
	void draw();
	void move(Position p1);
};

class Pacman {
private:
	int point;
	Position pPosition;
public:
	Pacman() {
		point = DEFAULT_POINT;
		pPosition = Position(0, 0);
	}
	void aStar(Map *map);
	void BFS(Map *map);
	bool isDestination(Map *map);
	void setPacman(int x, int y);
};

class Ghost {
private:

public:

};


float hEulCalculator(int posX, int posY, int targetX, int targetY); //Euclidean Distance

float power(int a);


#endif //PCH_H
