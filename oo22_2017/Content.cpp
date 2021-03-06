#include "Content.h"

Content* Content::content;

Content::Content(void) //ladataan sis�lt�. Tekstuureja, fontteja, etc.
{
	try {
		!playerTexture.loadFromFile("res/player.png");
	}
	catch (...){ printf("Error: Player texture not found!\n"); }
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
	debugText.setFillColor(sf::Color::White);
	font.loadFromFile("res\\calibri.ttf");
	blockTexture.loadFromFile("res/block.png");
	floorTexture.loadFromFile("res/floor.png");
	ladderTexture.loadFromFile("res/tikkaat.png");
	backgroundTexture1.loadFromFile("res\\kypala.png");
	cloudTexture.loadFromFile("res\\pilvi.png");
}

Content::~Content(void)
{
	free(content);
}
//Palautetaan pointteri t�h�n luokkaan, jolla p��st��n hakemaan Contentin sis�lt�� muualta.
Content* Content::get()
{
	if (!content)
		content = new Content();

	return content;
}
//Asetaan/p�ivitet��n debugTeksti
void Content::setDebugText(std::string text){
	debugText.setString(text);
}

void Content::setDebugTextPosition(float posX, float posY){
	debugText.setPosition(posX, posY);
}