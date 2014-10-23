#pragma once
#include <SFML\Graphics.hpp>

class Content
{
private:
	static Content* content;
	sf::Texture playerTex;
	sf::Texture backgroundTex;
	sf::Font calibri;
	sf::Text debugText;
	Content(void);
public:
	~Content(void);
	sf::Texture getPlayerTexture();
	sf::Font getCalibriFont();
	sf::Text getDebugText();
	static Content* get();

	void setDebugText(std::string text);
};

