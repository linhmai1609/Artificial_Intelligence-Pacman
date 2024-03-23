// Pacman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

int main()
{
	ifstream input;
	ofstream f;
	Map *map = new Map();
	Pacman *p = new Pacman();
	int attr, level, i, a;
	while (true) {
		cout << "Input level: ";
		cin >> level;
		switch (level) {
		case 1:
			a = rand() % 3 + 1;
			switch (a) {
			case 1:
				input.open("map11.txt", ios::in);
				i = 0;
				while (!input.eof()) {
					for (int j = 0; j < MAP_HEIGHT; ++j) {
						input >> attr;
						switch (attr)
						{
						case 2:
							map->foodPosition = Position(i, j);
							break;
						case 3:
							break;
						case 4:
							p->setPacman(i, j);
							break;
						default:
							break;
						}
						map->setAttr(i, j, attr);
					}
					++i;
				}
				f.open("output.txt", ios::ate | ios::app | ios::in);
				f << "Level: " << level << "\n";
				f << "Map: " << a << "\n";
				f.close();
				p->aStar(map);
				break;
			case 2: 
				input.open("map21.txt", ios::in);
				i = 0;
				while (!input.eof()) {
					for (int j = 0; j < MAP_HEIGHT; ++j) {
						input >> attr;
						switch (attr)
						{
						case 2:
							map->foodPosition = Position(i, j);
							break;
						case 3:
							break;
						case 4:
							p->setPacman(i, j);
							break;
						default:
							break;
						}
						map->setAttr(i, j, attr);
					}
					++i;
				}
				f.open("output.txt", ios::ate | ios::app | ios::in);
				f << "Level: " << level << "\n";
				f << "Map: " << a << "\n";
				f.close();
				p->aStar(map);
				break;
			case 3:
				input.open("map31.txt", ios::in);
				i = 0;
				while (!input.eof()) {
					for (int j = 0; j < MAP_HEIGHT; ++j) {
						input >> attr;
						switch (attr)
						{
						case 2:
							map->foodPosition = Position(i, j);
							break;
						case 3:
							break;
						case 4:
							p->setPacman(i, j);
							break;
						default:
							break;
						}
						map->setAttr(i, j, attr);
					}
					++i;
				}
				break;
			}
			f.open("output.txt", ios::ate | ios::app | ios::in);
			f << "Level: " << level << "\n";
			f << "Map: " << a << "\n";
			f.close();
			p->aStar(map);
			break;
		case 2:
			a = rand() % 3 + 1;
			switch (a) {
			case 1:
				input.open("map1.txt", ios::in);
				i = 0;
				while (!input.eof()) {
					for (int j = 0; j < MAP_HEIGHT; ++j) {
						input >> attr;
						switch (attr)
						{
						case 2:
							map->foodPosition = Position(i, j);
							break;
						case 3:
							break;
						case 4:
							p->setPacman(i, j);
							break;
						default:
							break;
						}
						map->setAttr(i, j, attr);
					}
					++i;
				}
				f.open("output.txt", ios::ate | ios::app | ios::in);
				f << "Level: " << level << "\n";
				f << "Map: " << a << "\n";
				f.close();
				p->aStar(map);
				break;
			case 2:
				input.open("map2.txt", ios::in);
				i = 0;
				while (!input.eof()) {
					for (int j = 0; j < MAP_HEIGHT; ++j) {
						input >> attr;
						switch (attr)
						{
						case 2:
							map->foodPosition = Position(i, j);
							break;
						case 3:
							break;
						case 4:
							p->setPacman(i, j);
							break;
						default:
							break;
						}
						map->setAttr(i, j, attr);
					}
					++i;
				}
				f.open("output.txt", ios::ate | ios::app | ios::in);
				f << "Level: " << level << "\n";
				f << "Map: " << a << "\n";
				f.close();
				p->aStar(map);
				break;
			case 3:
				input.open("map3.txt", ios::in);
				i = 0;
				while (!input.eof()) {
					for (int j = 0; j < MAP_HEIGHT; ++j) {
						input >> attr;
						switch (attr)
						{
						case 2:
							map->foodPosition = Position(i, j);
							break;
						case 3:
							break;
						case 4:
							p->setPacman(i, j);
							break;
						default:
							break;
						}
						map->setAttr(i, j, attr);
					}
					++i;
				}
				break;
			}
			f.open("output.txt", ios::ate | ios::app | ios::in);
			f << "Level: " << level << "\n";
			f << "Map: " << a << "\n";
			f.close();
			p->aStar(map);
			break;
		case 3:
			a = rand() % 2 + 1;
			switch (a) {
			case 1:
				input.open("map4.txt", ios::in);
				i = 0;
				while (!input.eof()) {
					for (int j = 0; j < MAP_HEIGHT; ++j) {
						input >> attr;
						switch (attr)
						{
						case 2:
							map->foodPosition = Position(i, j);
							break;
						case 3:
							break;
						case 4:
							p->setPacman(i, j);
							break;
						default:
							break;
						}
						map->setAttr(i, j, attr);
					}
					++i;
				}
				f.open("output.txt", ios::ate | ios::app | ios::in);
				f << "Level: " << level << "\n";
				f << "Map: " << a << "\n";
				f.close();
				p->BFS(map);
				break;
			case 2:
				input.open("map5.txt", ios::in);
				i = 0;
				while (!input.eof()) {
					for (int j = 0; j < MAP_HEIGHT; ++j) {
						input >> attr;
						switch (attr)
						{
						case 2:
							map->foodPosition = Position(i, j);
							break;
						case 3:
							break;
						case 4:
							p->setPacman(i, j);
							break;
						default:
							break;
						}
						map->setAttr(i, j, attr);
					}
					++i;
				}
				f.open("output.txt", ios::ate | ios::app | ios::in);
				f << "Level: " << level << "\n";
				f << "Map: " << a << "\n";
				f.close();
				p->BFS(map);
				break;
			}
			break;
		case 4:
			break;
		case 5:
			return 0;
		}		
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

