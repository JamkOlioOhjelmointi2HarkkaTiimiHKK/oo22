/*
* 17.10.2014 Tein tilakoneen ja annoin enumille mahdolliset tilat
* Tuomas Kyttä
*
*
*
* 
*/
#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
#include "Controls.h"
#include "Content.h"

class Button
{
private:
	sf::Font calibri;

public:
	Button(sf::Vector2f, std::string, std::function<void()>);
	Button(double x, double y, std::string, std::function<void()>);

	std::function<void()> function;

	sf::Vector2f position;
	sf::RectangleShape button;
	sf::Text buttonText;
	void update();
	void draw(sf::RenderWindow &window);

	~Button();
};

