/*
* 28.10.2014 Lis‰sin calibri fontin sek‰ debugText:n t‰h‰n luokkaan. Debug teksti‰ ei v‰ltt‰m‰tt‰ olisi tarvinnut tuoda t‰h‰n erikseen, mutta ajattelin sen olevan k‰tev‰ pidemm‰ll‰ t‰ht‰imell‰.
* Arttu Heinonen
*
*
*
*
*/
#pragma once
#include <SFML\Graphics.hpp>

class Content
{
private:
	static Content* content;

	Content(void);
public:
	~Content(void);
	sf::Texture playerTexture;
	sf::Texture janisTexture;
	sf::Texture ghostTexture;
	sf::Texture slimeTexture;
	sf::Texture gunHandTexture;
	sf::Texture backgroundTexture;
	sf::Font calibri;
	sf::Font font; // Tuomas K‰ytt‰‰ t‰t‰
	sf::Text debugText;

	static Content* get();

	void setDebugText(std::string text);
	void setDebugTextPosition(float posX, float posY);
};

