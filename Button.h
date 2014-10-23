#pragma once
#include "SFML/Graphics.hpp"
#include "main.h"
#include <functional>
#include "Controls.h"
#include "Content.h"

class Button
{
public:
	Button(sf::Vector2f, std::string, std::function<void()>);

	std::function<void()> function;

	sf::Vector2f position;
	sf::RectangleShape button;
	sf::Text buttonText;
	void update();
	void draw();

	~Button();
};

