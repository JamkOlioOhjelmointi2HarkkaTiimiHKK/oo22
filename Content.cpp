#include "Content.h"

Content* Content::content;

Content::Content(void) //ladataan sisältö
{
	//backgroundTex.loadFromFile("res/taivas.png");
	if (!playerTexture.loadFromFile("res/player.png")){
		printf("Error: Player texture not found!\n");
	}
	janisTexture.loadFromFile("res/janis.png");
	ghostTexture.loadFromFile("res/ghost.png");
	slimeTexture.loadFromFile("res/slime.png");
	foxTexture.loadFromFile("res/fox.png");
	gunHandTexture.loadFromFile("res/gunHand.png");
	if (!calibri.loadFromFile("res/calibri.ttf")){
		printf("Error: Calibri font not found!\n");
	}
	debugText.setFont(calibri);
	debugText.setString("0");
	debugText.setCharacterSize(24);
	debugText.setColor(sf::Color::White);
	font.loadFromFile("res\\calibri.ttf");
}

Content::~Content(void)
{
	free(content);
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

void Content::setDebugTextPosition(float posX, float posY){
	debugText.setPosition(posX, posY);
}