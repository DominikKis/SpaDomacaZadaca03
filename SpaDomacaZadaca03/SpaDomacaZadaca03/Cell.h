#pragma once
#include <SFML/Graphics.hpp>
class Cell
{
public:
	bool wall;
	bool scaned;
	bool A;
	bool B;
	bool path;
	int X;
	int Y;
	int iteration;
	Cell();
	void render(unsigned int x, unsigned int y, sf::RenderWindow* window);
};

