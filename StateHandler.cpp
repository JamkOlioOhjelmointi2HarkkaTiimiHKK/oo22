#include "StateHandler.h"


StateHandler::StateHandler()
{
	state = uninitialized;
	//editState = new EditorState();
	//mainMenu = new MainMenu();

}
/*
void StateHandler::showMenu()
{	
	mainMenu->update();
	window.clear(sf::Color().White);
	mainMenu->draw();
	//TEMP
	dt = time1.restart().asSeconds();
	fps.setString(std::to_string((int)(1/dt)));
	window.draw(fps);
	window.display();

	MainMenu::menuResult result = mainMenu->action;

	switch (result)
	{
	case MainMenu::merge:
		state = exit; // tilapäinen
		break;
	case MainMenu::edit:
		state = edit; // voi hyvää päivää nimeämisen kanssa, toimii kuitenkin kuin junan vessa
		break;
	}

}
*/
void StateHandler::editStart()
{
	if (state != uninitialized)
		return;
	state = menu;

	while (!editExit())
	{			
		editLoop();
	}

	window.close();
}

bool StateHandler::editExit()
{
	if (state == exit)
		return true;
	else
		return false;
}

void StateHandler::editLoop()
{	
	sf::Event currentEvent;
	if (window.pollEvent(currentEvent))
	{
		if (currentEvent.type == sf::Event::Closed)
			state = exit;

	}

	Controls::get()->update();
	switch (state)
	{
	case menu:
	{
		showMenu();
		break;
	}

	case edit:
	{
				 editState->update();
				 window.clear(sf::Color(255, 0, 0));
				 editState->draw();
				 window.display();

				 if (Controls::get()->kIsPressed(sf::Keyboard().Escape))
				 {
					 mainMenu->unInitialize();
					 state = menu;

				 }

	}
	}
}

StateHandler::~StateHandler()
{
	delete editState;
	delete mainMenu;
}
