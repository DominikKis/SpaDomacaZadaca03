#include "Cell.h"
#include <SFML/Graphics.hpp>

Cell::Cell()
{
	wall = 0;
	scaned = 0;
	path = 0;
	iteration = 0;
	A = 0;
	B = 0;
}

void Cell::render(unsigned int x, unsigned int y, sf::RenderWindow* window)
{
	sf::RectangleShape cell(sf::Vector2f(20, 20));
	cell.setPosition(20 * x,20 * y);
	if (wall)
	{
		cell.setFillColor(sf::Color(46, 46, 46));
	}
	else if (A)
	{
		cell.setFillColor(sf::Color(255, 255, 255));
	}
	else if (B)
	{
		cell.setFillColor(sf::Color(255, 0, 25));
	}
	else if (path)
	{
		cell.setFillColor(sf::Color(141, 252, 252));
	}
	else
	{
		cell.setFillColor(sf::Color(0, 186, 25));
	}
	window->draw(cell);
}
