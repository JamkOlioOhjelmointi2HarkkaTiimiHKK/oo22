#include "StateHandler.h"
#include "globals.h"


sf::RenderWindow window(sf::VideoMode(1024, 768), "Editor");

int main()
{
	
	StateHandler game;
	game.startGame();

    return 0;
}