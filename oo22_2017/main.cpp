#include "StateHandler.h"
#include "globals.h"


sf::RenderWindow window(sf::VideoMode(0, 0), "PotkuStart");

int main()
{
	
	StateHandler game;
	game.startGame();

    return 0;
}