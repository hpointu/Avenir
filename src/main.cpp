#include "game/Game.hpp"
#include <iostream>
int main()
{
	Game *g = Game::getInstance();
	g->init();
	g->run();

	return 0;
}
