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
#include "globals.h"

class Button
{
private:
	sf::Font calibri;

public:
	Button(){};
	Button(sf::Vector2f, std::string, std::function<void()>, sf::Vector2f size = (sf::Vector2f(150, 150)));
	Button(double x, double y, std::string, std::function<void()>, sf::Vector2f size = (sf::Vector2f(150, 150)));

	Button(sf::Vector2f, sf::Vector2f, std::string, std::function<void()>);
	
	std::function<void()> function;

	sf::Vector2f position;
	sf::RectangleShape button;
	sf::Text buttonText;
	bool isMouseOverButton;

	void initialize(sf::Vector2f position, std::function<void()>, sf::Vector2f size = (sf::Vector2f(150, 150)), std::string text = "");
	void update();
	void draw(sf::RenderWindow &window);
	void draw();
	void setSize(sf::Vector2f);
	void setColor(sf::Color);
	void setColor(int, int, int);

	~Button();
};

