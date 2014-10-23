#include <SFML/Graphics.hpp>
#include "player.h"
#include "globals.h"
#include "Controls.h"
#include "Content.h"
using namespace sf;



int main()
{
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO2");
	window.setVerticalSyncEnabled(true);

	Font calibri;
	if(!calibri.loadFromFile("res/calibri.ttf")){
		printf("Error: font not found!\n");
	}
	Text debugText;
	debugText.setFont(calibri);
	debugText.setString("0");
	debugText.setCharacterSize(24);
	debugText.setColor(Color::White);

	Clock clock;
	Time elapsedTime = clock.restart(); 
	int fps = 0;

	Player player();

    while (window.isOpen())
    {	
		elapsedTime = clock.getElapsedTime();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
		if (Controls::get()->iskeydown(Keyboard::Escape)){
			window.close();
		}

		//Logic here		
		Controls::get()->update();

		//FPS
		if(elapsedTime.asMilliseconds() >= 1000){
			clock.restart();
			debugText.setString(std::to_string(fps));
			fps = 0;
		}
		else{
			fps++;
		}


		//Draw here
		window.clear(Color::Black);
		window.draw(debugText);
        window.display();
    }

    return 0;
}