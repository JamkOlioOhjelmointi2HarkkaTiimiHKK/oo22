/*
* 28.10.2014 Lisäsin calibri fontin sekä debugText:n tähän luokkaan. Debug tekstiä ei välttämättä olisi tarvinnut tuoda tähän erikseen, mutta ajattelin sen olevan kätevä pidemmällä tähtäimellä.
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
	sf::Texture backgroundTexture;
	sf::Font calibri;
	sf::Text debugText;

	static Content* get();

	void setDebugText(std::string text);
};

