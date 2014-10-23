#include "Content.h"

Content* Content::content;

Content::Content(void) //ladataan sisältö
{
	//backgroundTex.loadFromFile("res/taivas.png");
	if (!playerTex.loadFromFile("res/player.png")){
		printf("Error: Player texture not found!\n");
	}
	if (!calibri.loadFromFile("res/calibri.ttf")){
		printf("Error: font not found!\n");
	}

}

Content::~Content(void)
{

}

sf::Texture Content::getPlayerTexture()
{
	return this->playerTex;
}

sf::Font Content::getCalibriFont()
{
	return this->calibri;
}

Content* Content::get()
{
	if (!content)
		content = new Content();

	return content;
}