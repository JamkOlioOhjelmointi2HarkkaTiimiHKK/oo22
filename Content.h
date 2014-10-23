#pragma once
#include <SFML\Graphics.hpp>

class Content
{
private:
	static Content* content;
	sf::Texture playerTex;
	sf::Texture backgroundTex;
	sf::Font calibri;
	Content(void);
public:
	~Content(void);
	sf::Texture getPlayerTexture();
	sf::Font getCalibriFont();
	static Content* get();
};

