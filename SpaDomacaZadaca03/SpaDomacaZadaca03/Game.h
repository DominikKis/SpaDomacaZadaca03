#pragma once
#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Game
{
public:
	Game(Cell** theCells, int ax, int ay,unsigned int x, unsigned int y);
	void loadRender(sf::RenderWindow* window);
	void render();
	void Scaning();
	void Path();
	stack<Cell> scaned;
private:
	Cell position;
	queue<int>scanX;
	queue<int>scanY;
	queue<int>scanXN;
	queue<int>scanYN;
	//stack<int>pathX;
	//stack<int>pathY;
	stack<Cell> path;
	Cell** theCells;
	Cell** theCellsCopy;
	unsigned int MaxX;
	unsigned int MaxY;
	sf::RenderWindow* window;
	bool getNeighbours(unsigned int x, unsigned int y);
	void pathCalculater();
};

