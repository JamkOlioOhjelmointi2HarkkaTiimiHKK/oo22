#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Controls
{
	bool curkeys[256];
	bool oldkeys[256];
	sf::Vector2i mpos;	//mpos = mouse position
	bool curmousekeys[3];
	bool oldmousekeys[3];
	static Controls* controls;
	Controls(void);
public:
	void update();
	bool iskeydown(sf::Keyboard::Key key);
	bool kIsPressed(sf::Keyboard::Key key);
	bool kIsReleased(sf::Keyboard::Key key);
	bool miskeydown(sf::Mouse::Button key);
	bool mIsPressed(sf::Mouse::Button key);
	bool mIsReleased(sf::Mouse::Button key);
	sf::Vector2f getmousepos();
	~Controls(void);
	static Controls* get();
};

