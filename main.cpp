#include <SFML/Graphics.hpp>
#include "player.h"
#include "globals.h"
#include "Controls.h"
#include "Content.h"
using namespace sf;



int main()
{
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22");
	window.setVerticalSyncEnabled(true);

	bool showDebug = true;

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
		if (Controls::get()->kIsReleased(Keyboard::F1)){
			showDebug = !showDebug;
		}

		//Logic here		
		Controls::get()->update();

		//FPS
		if(elapsedTime.asMilliseconds() >= 1000){
			clock.restart();
			Content::get()->setDebugText(std::to_string(fps));
			fps = 0;
		}
		else{
			fps++;
		}


		//Draw here
		window.clear(Color::Black);
		if (showDebug){
			window.draw(Content::get()->debugText);
		}
        window.display();
    }

    return 0;
}