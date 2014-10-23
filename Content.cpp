#include "Content.h"

Content* Content::content;

Content::Content(void) //ladataan sis�lt�
{
	//backgroundTex.loadFromFile("res/taivas.png");
	if (!playerTex.loadFromFile("res/player.png")){
		printf("Error: Player texture not found!\n");
	}
	if (!calibri.loadFromFile("res/calibri.ttf")){
		printf("Error: Calibri font not found!\n");
	}
	debugText.setFont(calibri);
	debugText.setString("0");
	debugText.setCharacterSize(24);
	debugText.setColor(sf::Color::White);

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

sf::Text Content::getDebugText(){
	return this->debugText;
}

Content* Content::get()
{
	if (!content)
		content = new Content();

	return content;
}

void Content::setDebugText(std::string text){
	debugText.setString(text);
}