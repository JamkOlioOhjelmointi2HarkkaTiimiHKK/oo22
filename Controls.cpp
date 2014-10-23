#include "Controls.h"

Controls* Controls::controls; // pointteri controls controls namespacesta

void Controls::update() 
{
	mpos = sf::Mouse::getPosition();

	for(int i=0;i<255;++i)
	{
		oldkeys[i]=curkeys[i];
		curkeys[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
	}

	for(int i=0;i<3;++i)
	{
		oldmousekeys[i]=curmousekeys[i];
		curmousekeys[i] = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
	}
}

bool Controls::iskeydown(sf::Keyboard::Key key)
{
	return curkeys[(int)key];
}

bool Controls::kIsPressed(sf::Keyboard::Key key)
{
	if(curkeys[(int)key] && !oldkeys[(int)key])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controls::kIsReleased(sf::Keyboard::Key key)
{
	if(!curkeys[(int)key] && oldkeys[(int)key])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controls::miskeydown(sf::Mouse::Button key)
{
	return curmousekeys[(int)key];
}

bool Controls::mIsPressed(sf::Mouse::Button key)
{
	if(curmousekeys[(int)key] && !oldmousekeys[(int)key])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controls::mIsReleased(sf::Mouse::Button key)
{
	if(!curmousekeys[(int)key] && oldmousekeys[(int)key])
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::Vector2f Controls::getmousepos()
{
	return (sf::Vector2f)mpos;
}

Controls::Controls(void)
{
	for(int i=0;i<255;++i)
	{
		oldkeys[i]=false;
		curkeys[i] = false;
	}

	for(int i=0;i<3;++i)
	{
		oldmousekeys[i]=false;
		curmousekeys[i] = false;
	}
}

Controls::~Controls(void)
{

}

Controls* Controls::get()
{
	if (!controls)
		controls = new Controls();

	return controls;
}