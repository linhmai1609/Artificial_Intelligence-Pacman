// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

// In general, ignore this file, but keep it around if you are using pre-compiled headers.
void Pacman::aStar(Map *map) {
	clock_t start;
	double duration;

	start = std::clock();

	float gn[4];		
	ofstream f;
	Map *dup = map;
	int count = 0;
	int test;	
	int newX =0, newY=0;
	bool visited[MAP_HEIGHT][MAP_WIDTH];

	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			visited[i][j] = false;

	while (!isDestination(map)) {
		count++;
		map->InitGraphic();
		map->draw();
		int count = 0;
		memset(gn, 0, sizeof(gn));
		for (int i = 0; i < 4; i++) {
			switch (i)
			{
			case 0:
				test = map->getPosition(pPosition.getX(), pPosition.getY() + 1);
				if (map->getPosition(pPosition.getX(), pPosition.getY() + 1) != 1 && map->getPosition(pPosition.getX(), pPosition.getY() + 1) != 3 && !visited[pPosition.getY() + 1][pPosition.getX()]) {
					gn[0] = hEulCalculator(pPosition.getX(), pPosition.getY() + 1, map->foodPosition.getX(), map->foodPosition.getY()) + 1;
				}
				else {
					gn[0] = -1;
					count++;
				}
				break;
			case 1:
				if (map->getPosition(pPosition.getX(), pPosition.getY() - 1) != 1 && map->getPosition(pPosition.getX(), pPosition.getY() - 1) != 3 && !visited[pPosition.getY() - 1][pPosition.getX()]) {					
					gn[1] = hEulCalculator(pPosition.getX(), pPosition.getY() - 1, map->foodPosition.getX(), map->foodPosition.getY()) + 1;
				}
				else {
					gn[1] = -2;
					count++;
				}
				break;
			case 2:
				if (map->getPosition(pPosition.getX() - 1, pPosition.getY()) != 1 && map->getPosition(pPosition.getX() - 1, pPosition.getY()) != 3 && !visited[pPosition.getY()][pPosition.getX() - 1]){
						gn[2] = hEulCalculator(pPosition.getX() - 1, pPosition.getY(), map->foodPosition.getX(), map->foodPosition.getY()) + 1;
				}
				else {
					gn[2] = -3;
					count++;
				}
				break;
			case 3:
				if (map->getPosition(pPosition.getX() + 1, pPosition.getY()) != 1 && map->getPosition(pPosition.getX() + 1, pPosition.getY() + 1) != 3 && !visited[pPosition.getY()][pPosition.getX() + 1]) {
					
					gn[3] = hEulCalculator(pPosition.getX() + 1, pPosition.getY(), map->foodPosition.getX(), map->foodPosition.getY()) + 1;
				}
				else {
					gn[3] = -4;
					count++;
				}
				break;
			}
		}
		/*if (count >= 4) {
			cout << "Dead end! The solution is not exist!" << endl;
			return;
		}*/
		float oriGn[4];
		int pos[4];
		memset(pos, -1, sizeof(pos));
		for (int i = 0; i < 4; ++i) {
			oriGn[i] = gn[i];
		}
		int n = sizeof(gn) / sizeof(gn[0]);
		sort(gn, gn + n);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (oriGn[i] == gn[j] && oriGn[i] > 0) {
					pos[j] = i;
					break;
				}
			}
		}

		int flag = 0;
		for (int i = 0; i < 4; i++) {
			switch (pos[i]) {
			case 0:				
					newX = pPosition.getX();
					newY = pPosition.getY() + 1;
					flag = 1;
					break;
			case 1:
					newX = pPosition.getX();
					newY = pPosition.getY() - 1;
					flag = 1;				
					break;
			case 2:
					newX = pPosition.getX() - 1;
					newY = pPosition.getY();
					flag = 1;
					break;
			case 3:
					newX = pPosition.getX() + 1;
					newY = pPosition.getY();
					flag = 1;
					break;
			default:
				break;
			}
			if (flag == 1)
				break;
		}
		int oldX = pPosition.getX(); 
		int oldY = pPosition.getY();
		if (count >= 4) {
			memset(visited, false, sizeof(visited));
		}
		visited[newY][newX] = true;		
		setPacman(newX, newY);
		pPosition.setParent(oldX, oldY);
		map->setAttr(pPosition.getPX(), pPosition.getPY(), 0);
		map->setAttr(pPosition.getX(), pPosition.getY(), 4);			
		map->move(pPosition);		
		Sleep(500);
	}
	map->InitGraphic();
	map->draw();
	count++;
	cout << "Destination reached!" << endl;

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	//Write file
	f.open("output.txt", ios::ate | ios::app | ios::in);
	f << "Status: Destination reached!\n";
	f << "Number of steps: " << count << "\n";
	f << "Time: " << duration << "s" << '\n';
	f << '\n';
	f.close();
	return;
}

void Pacman::BFS(Map *map) {
	ofstream f;
	clock_t start;
	double duration;

	start = std::clock();

	//Init graphics
	map->InitGraphic();
	map->draw();
	//BFS
	bool visited[MAP_HEIGHT][MAP_WIDTH];
	int totalCount = 0;
	while (true) {
		for (int i = 0; i < MAP_WIDTH; i++)
			for (int j = 0; j < MAP_HEIGHT; j++)
				visited[j][i] = false; 
		
		visited[pPosition.getY()][pPosition.getX()] = true;

		Position *newPosition = new Position(pPosition.getX(), pPosition.getY());
		Position *currPosition = new Position(pPosition.getX(), pPosition.getY());
		Position *food;
		bool flag = false;
		int count = 0;
		list<Position> queue;
		list<Position> expanded;

		newPosition->setParent(-1, -1);
		queue.push_back(*newPosition);

		while (!queue.empty()) {
			*newPosition = queue.front();
			expanded.push_back(*newPosition);
			queue.pop_front();

			for (int dir = 0; dir < 4; ++dir) {
				switch (dir)
				{
				case 0:
					currPosition = new Position(newPosition->getX(), newPosition->getY());
					if (!visited[currPosition->getY()][currPosition->getX() + 1]) {
						if (map->getPosition(currPosition->getX() + 1, currPosition->getY()) == 1 || map->getPosition(currPosition->getX() + 1, currPosition->getY()) == 3) {
							visited[currPosition->getY()][currPosition->getX() + 1] = true;
						}
						else if (map->getPosition(currPosition->getX() + 1, currPosition->getY()) == 2) {
							visited[currPosition->getY()][currPosition->getX() + 1] = true;
							newPosition = new Position(newPosition->getX() + 1, newPosition->getY());
							newPosition->setParent(newPosition->getX() - 1, newPosition->getY());
							expanded.push_back(*newPosition);
							queue.pop_front();							
							flag = true;
							break;
						}
						else {
							visited[currPosition->getY()][currPosition->getX() + 1] = true;
							currPosition = new Position(currPosition->getX() + 1, currPosition->getY());
							currPosition->setParent(currPosition->getX() - 1, currPosition->getY());
							queue.push_back(*currPosition);
						}
						break;
					}
				case 1:
					currPosition = new Position(newPosition->getX(), newPosition->getY());
					if (!visited[currPosition->getY() - 1][currPosition->getX()]) {
						if (map->getPosition(currPosition->getX(), currPosition->getY() - 1) == 1 || map->getPosition(currPosition->getX(), currPosition->getY() - 1) == 3) {
							visited[currPosition->getY() - 1][currPosition->getX()] = true;
						}
						else if (map->getPosition(currPosition->getX(), currPosition->getY() - 1) == 2) {
							visited[currPosition->getY() - 1][currPosition->getX()] = true;
							newPosition = new Position(newPosition->getX(), newPosition->getY() - 1);
							newPosition->setParent(newPosition->getX(), newPosition->getY() + 1);
							expanded.push_back(*newPosition);
							queue.pop_front();
							flag = true;
							break;
						}
						else {
							visited[currPosition->getY() - 1][currPosition->getX()] = true;
							currPosition = new Position(currPosition->getX(), currPosition->getY() - 1);
							currPosition->setParent(currPosition->getX(), currPosition->getY() + 1);
							queue.push_back(*currPosition);
						}
						break;
					}
				case 2:
					currPosition = new Position(newPosition->getX(), newPosition->getY());
					if (!visited[currPosition->getY()][currPosition->getX() - 1]) {
						if (map->getPosition(currPosition->getX() - 1, currPosition->getY()) == 1 || map->getPosition(currPosition->getX() - 1, currPosition->getY()) == 3) {
							visited[currPosition->getY()][currPosition->getX() - 1] = true;
						}
						else if (map->getPosition(currPosition->getX() - 1, currPosition->getY()) == 2) {
							visited[currPosition->getY() - 1][currPosition->getX()] = true;
							newPosition = new Position(newPosition->getX() - 1, newPosition->getY());
							newPosition->setParent(newPosition->getX() + 1, newPosition->getY());
							expanded.push_back(*newPosition);
							queue.pop_front();
							flag = true;
							break;
						}
						else {
							visited[currPosition->getY()][currPosition->getX() - 1] = true;
							currPosition = new Position(currPosition->getX() - 1, currPosition->getY());
							currPosition->setParent(currPosition->getX() + 1, currPosition->getY());
							queue.push_back(*currPosition);
						}
						break;
					}
				case 3:
					currPosition = new Position(newPosition->getX(), newPosition->getY());
					if (!visited[currPosition->getY() + 1][currPosition->getX()]) {
						if (map->getPosition(currPosition->getX(), currPosition->getY() + 1) == 1 || map->getPosition(currPosition->getX(), currPosition->getY() + 1) == 3) {
							visited[currPosition->getY() + 1][currPosition->getX()] = true;
						}
						else if (map->getPosition(currPosition->getX(), currPosition->getY() + 1) == 2) {
							visited[currPosition->getY() + 1][currPosition->getX()] = true;
							newPosition = new Position(newPosition->getX(), newPosition->getY() + 1);
							newPosition->setParent(newPosition->getX(), newPosition->getY() - 1);
							expanded.push_back(*newPosition);
							queue.pop_front();
							flag = true;
							break;
						}
						else {
							visited[currPosition->getY() + 1][currPosition->getX()] = true;
							currPosition = new Position(currPosition->getX(), currPosition->getY() + 1);
							currPosition->setParent(currPosition->getX(), currPosition->getY() - 1);
							queue.push_back(*currPosition);
						}
						break;
					}
				}
			}
			if (flag) {
				break;
			}
		}
		//Pos-procedures
		list<Position> result;
		list<Position>::iterator iterInt;

		if (!flag) {
			map->draw();
			map->InitGraphic();
			Sleep(500);
			cout << "No food can be found! Stop the game!" << endl;
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

			//Write file
			f.open("output.txt", ios::ate | ios::app | ios::in);
			f << "Status: No food can be found!\n";
			f << "Number of steps: " << totalCount << "\n";
			f << "Time: " << duration << "s" << '\n';
			f << '\n';
			f.close();
			return;
		}
		else {
			while (true) {
				result.push_front(*newPosition);

				if (newPosition->getPX() == -1)
					break;

				for (iterInt = expanded.begin(); iterInt != expanded.end(); ++iterInt) {
					if (iterInt->getX() == newPosition->getPX() && iterInt->getY() == newPosition->getPY()) {
						newPosition = new Position(iterInt->getX(), iterInt->getY());
						newPosition->setParent(iterInt->getPX(), iterInt->getPY());
						break;
					}
				}
			}
		}
		for (iterInt = result.begin(); iterInt != result.end(); ++iterInt) {
			count++;
		}
		if (9 - count >= 0) {
			totalCount += count;
			while (!result.empty()) {
				*newPosition = result.front();
				//Do some graphics things				

				if (newPosition->getPX() != -1) {
					map->setAttr(newPosition->getPX(), newPosition->getPY(), 0);
					map->setAttr(newPosition->getX(), newPosition->getY(), 4);
					map->move(*newPosition);
					map->draw();
					map->InitGraphic();
					Sleep(500);
				}		
				result.pop_front();
			}
			this->pPosition = *newPosition;
		}
		else {
			cout << "The cost is too much for Pacman to travel! Stop the game!" << endl;
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

			//Write file
			f.open("output.txt", ios::ate | ios::app | ios::in);
			f << "Status: High cost!\n";
			f << "Number of steps: " << totalCount << "\n";
			f << "Time: " << duration << "s" << '\n';
			f.close();
			return;
		}
	}
}

bool Pacman::isDestination(Map *map)
{
	if (pPosition.getX() == map->foodPosition.getX() && pPosition.getY() == map->foodPosition.getY())
		return true;
	else
		return false;
}

void Pacman::setPacman(int x, int y) {
	Position *p = new Position(x, y);
	this->pPosition = *p;
}

void Map::InitGraphic()
{
	mapGraphics[0][0] = char(TOPLEFT);
	mapGraphics[0][MAP_WIDTH - 1] = char(BOTLEFT);
	mapGraphics[MAP_HEIGHT-1][0] = char(TOPRIGHT);
	mapGraphics[MAP_WIDTH-1][MAP_HEIGHT-1] = char(BOTRIGHT);
	for (int i = 0; i < MAP_WIDTH; i += (MAP_WIDTH - 1)) {
		for (int j = 1; j < MAP_HEIGHT - 1; j++)
			mapGraphics[j][i] = char(DOWN_EDGE);
	}
	for (int i = 0; i < MAP_HEIGHT; i += (MAP_HEIGHT - 1)) {
		for (int j = 1; j < MAP_WIDTH - 1; j++)
			mapGraphics[i][j] = char(UP_EDGE);
	}
	for (int i = 1; i < MAP_WIDTH - 1; i++) {
		for (int j = 1; j < MAP_HEIGHT - 1; j++) {
			switch (mapIndexes[j][i]) {
			case 1:
				mapGraphics[j][i] = char(WALL);
				break;
			case 2:
				mapGraphics[j][i] = char(FOOD);
				break;
			case 3:
				mapGraphics[j][i] = char(GHOST);
				break;
			case 4:
				mapGraphics[j][i] = char(PACMAN);
				break;
			case 5:
				mapGraphics[j][i] = char(GO);
			default:
				break;
			}
		}
	}
}

void Map::draw()
{
	ClearScreen();
	for (int i = 0; i < MAP_WIDTH; ++i) {
		for (int j = 0; j < MAP_HEIGHT; ++j)
			cout << mapGraphics[j][i];
		cout << endl;
	}
}

void Map::move(Position p1)
{
	mapIndexes[p1.getPY()][p1.getPX()] = 5;
	mapIndexes[p1.getY()][p1.getX()] = 4;
	return;
}

//Map
int Map::getPosition(int x, int y) {
	return this->mapIndexes[y][x];
}

void Map::setMap(ifstream f) {
	switch (level) {
	case 1:
		f.open("Map1.txt");
		break;
	case 2:
		f.open("Map2.txt");
		break;
	case 3:
		f.open("Map3.txt");
		break;
	case 4:
		f.open("Map4.txt");
		break;
	}

}

void Map::setAttr(int x, int y, int attr)
{
	mapIndexes[y][x] = attr;
}

float hEulCalculator(int posX, int posY, int targetX, int targetY) {
	return sqrt(power(posX - targetX) + power(posY - targetY)); //Euclidean heuristic
	//return abs(posX - targetX) + abs(posY - targetY); // Manhattan distance heuristic
}

float power(int a) {
	return a * a;
}


//Clear screen (for Windows only)
void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}