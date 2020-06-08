#include "Game.h"

Game::Game(Cell** theCells, int ax, int ay,unsigned int x, unsigned int y)
{
	this->theCells = theCells;
	scanX.push(ax - 1);
	scanY.push(ay - 1);
	scaned.push(theCells[ax -1][ay -1]);
	MaxX = x;
	MaxY = y;
}

bool Game::getNeighbours(unsigned int x, unsigned int y)
{
	if (!(y == 0))
	{
		if (theCells[x][y - 1].scaned == 0)
		{
			scanXN.push(x);
			scanYN.push(y - 1);
			theCells[x][y - 1].scaned = true;
			theCells[x][y - 1].iteration = theCells[x][y].iteration + 1;
			scaned.push(theCells[x][y - 1]);
			if (theCells[x][y - 1].B)
			{
				return true;
			}
		}
	}
	if (!(x == 0))
	{
		if (theCells[x - 1][y].scaned == 0)
		{
			scanXN.push(x - 1);
			scanYN.push(y);
			theCells[x - 1][y].scaned = true;
			theCells[x - 1][y].iteration = theCells[x][y].iteration + 1;
			scaned.push(theCells[x - 1][y]);
			if (theCells[x - 1][y].B)
			{
				return true;
			}
		}
	}
	if (!(x == MaxX - 1))
	{
		if (theCells[x + 1][y].scaned == 0)
		{
			scanXN.push(x + 1);
			scanYN.push(y);
			theCells[x + 1][y].scaned = true;
			theCells[x + 1][y].iteration = theCells[x][y].iteration + 1;
			scaned.push(theCells[x + 1][y]);
			if (theCells[x + 1][y].B)
			{
				return true;
			}
		}
	}
	if (!(y == MaxY - 1))
	{
		if (theCells[x][y + 1].scaned == 0)
		{
			scanXN.push(x);
			scanYN.push(y + 1);
			theCells[x][y + 1].scaned = true;
			theCells[x][y + 1].iteration = theCells[x][y].iteration + 1;
			scaned.push(theCells[x][y + 1]);
			if (theCells[x][y + 1].B)
			{
				return true;
			}
		}
	}

	return false;
}

void Game::Scaning()
{
	bool found = false;
	while (!found)
	{
		while (!scanX.empty() && !scanY.empty())
		{
			if (getNeighbours(scanX.front(), scanY.front()))
			{
				found = true;
				break;
			}
			scanX.pop();
			scanY.pop();
		}
		scanX = scanXN;
		scanY = scanYN;
		while (!scanXN.empty() && !scanYN.empty())
		{
			scanXN.pop();
			scanYN.pop();
		}
	}
	pathCalculater();
}

void Game::Path()
{
	if (!path.empty())
	{
		theCells[path.top().X][path.top().Y].path = true;
		path.pop();
	}

}

void Game::loadRender(sf::RenderWindow* window)
{
	this->window = window;
}

void Game::render()
{
	for (int i = 0; i < MaxX; i++)
	{
		for (int j = 0; j < MaxY; j++)
		{
			theCells[i][j].render(i, j, window);
		}
	}
}

void Game::pathCalculater()
{
	position = scaned.top();
	path.push(scaned.top());
	scaned.pop();

	while (!scaned.empty())
	{
		if (scaned.top().iteration == position.iteration - 1)
		{
			
			if (scaned.top().X == position.X)
			{
				if (scaned.top().Y == position.Y - 1)
				{
					path.push(scaned.top());
					position = scaned.top();
				}
				else if (scaned.top().Y == position.Y + 1)
				{
					path.push(scaned.top());
					position = scaned.top();
				}
			}

			if (scaned.top().Y == position.Y)
			{
				if (scaned.top().X == position.X - 1)
				{
					path.push(scaned.top());
					position = scaned.top();
				}
				else if (scaned.top().X == position.X + 1)
				{
					path.push(scaned.top());
					position = scaned.top();
				}
			}
		}

		scaned.pop();

	}

}
