#include "Load.h"
using namespace std;

bool random(unsigned int chance) {
	bool wall;
	wall = ((rand() % 100) < chance);
	return wall;
}

Cell** reservation(unsigned int x, unsigned int y) {

	Cell** theCells = new Cell * [x];
	for (unsigned int i = 0; i < x; i++)
	{
		theCells[i] = new Cell[y];
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			theCells[i][j].X = i;
			theCells[i][j].Y = j;
		}
	}

	return theCells;
}

void walls(Cell** theCells) {

	for (int i = 0; i < 9; i++)
	{
		theCells[i][2].wall = true;
		theCells[i][2].scaned = true;
	}

}

void checkEvent(sf::Window* window,int &delay, bool &paused) {
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else if (sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				delay += 50;
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				delay -= 50;
				if (delay < 0)
				{
					delay = 0;
				}
			}
			else if (event.key.code == sf::Keyboard::P)
			{
				paused = true;
			}
			else if (event.key.code == sf::Keyboard::O)
			{
				paused = false;
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
		}
	}
}

void maploader(Cell** theCells, ifstream *in) {
	
	stringstream ss;
	string line;
	int j = 0;
	while (getline(*in, line))
	{
		for (int i = 0; i < 40; i++)
		{
			if (line[i] == '#')
			{
				theCells[i][j].wall = true;
				theCells[i][j].scaned = true;
			}
		}
		j++;
	}

}

//void firstFrameFix(Cell** theCells, int x, int y, sf::RenderWindow* window ) {
//
//	window->clear(sf::Color(0, 0, 0));
//	for (int i = 0; i < y; i++)
//	{
//		for (int j = 0; j < x; j++)
//		{
//
//			sf::RectangleShape cell(sf::Vector2f(10, 10));
//			cell.setPosition(1 + 11 * j, 1 + 11 * i);
//			if (theCells[i][j].wall)
//			{
//				cell.setFillColor(sf::Color(141, 252, 252));
//			}
//			else
//			{
//				cell.setFillColor(sf::Color(46, 46, 46));
//			}
//			window->draw(cell);
//		}
//	}
//	window->display();
//	auto start = chrono::steady_clock::now();
//	auto end = chrono::steady_clock::now();
//	int delay = 2000;
//	bool paused = false;
//	while (!((chrono::duration_cast<chrono::milliseconds>(end - start)) > chrono::milliseconds(2000)))
//	{
//		checkEvent(window, delay, paused);
//		end = chrono::steady_clock::now();
//	}
//}

void info() {

	cout << "U can change the delay between simulations with arrow key UP (longer delay) and arrow key down (smaller delay)" << endl <<
		"to pause the game press P and to continue press O" << endl;

}

int main()
{
	cout << "Ako upisete za velicinu gameboarda x = 0 i y = 0 onda ce biti ucitana labirint (Map1)" <<
		endl << "velicine 40x40 u svakom kutu sigurno nema zida" << endl;
	cout << "How big should the gameboard be?" << endl << "Width(x): ";
	unsigned int x;
	cin >> x;
	cout << "Height(y): ";
	unsigned int y;
	cin >> y;

	system("cls");

	bool map = 0;

	if (x == 0 && y == 0)
	{
		map = 1;
		x = 40;
		y = 40;
	}

	system("cls");
	
	Cell** theCells = reservation(x, y);

	if (map)
	{
		ifstream in("Map1.txt");
		if (!in) {
			cout << "Pogreska kod otvaranja datoteke" << endl;
			return 1;
		}
		maploader(theCells, &in);
	}

	unsigned int ax;
	unsigned int ay;
	unsigned int bx;
	unsigned int by;

	do
	{
		cout << "A stupac(x): ";
		cin >> ax;
		cout << "A redak(y): ";
		cin >> ay;
		cout << "B stupac(x): ";
		cin >> bx;
		cout << "B redak(y): ";
		cin >> by;

		system("cls");

	} while (theCells[ax - 1][ay - 1].wall || theCells[bx - 1][by - 1].wall);


	//walls(theCells);

	theCells[ax - 1][ay - 1].A = true;
	theCells[bx - 1][by - 1].B = true;

	Game game(theCells, ax, ay, x, y);
	game.Scaning();

	sf::RenderWindow window(sf::VideoMode(20 * x,20 * y), "Hello, SFML world!");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	game.loadRender(&window);

	info();

	bool paused = false;

	int delay = 400;

	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();

	while (window.isOpen())
	{
		checkEvent(&window, delay, paused);
		if (!paused)
		{
			if ((chrono::duration_cast<chrono::milliseconds>(end - start)) > chrono::milliseconds(delay))
			{
				start = chrono::steady_clock::now();
				game.Path();
			}
		}
		window.clear(sf::Color(0, 0, 0));
		game.render();
		window.display();
		end = chrono::steady_clock::now();
	}

	return 0;
}