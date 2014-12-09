#include "Gun.h"

Gun::Gun(){
	
}
Gun::~Gun(){

}

void Gun::create(sf::Sprite sprite){
	handSprite.setTexture(Content::get()->gunHandTexture);
	handSprite.setOrigin(5,0);
	handSprite.setPosition(sprite.getPosition().x - 5, sprite.getPosition().y);
}

void Gun::update(sf::Sprite sprite, bool isFacingLeft){

	updateCursor();

	if (isFacingLeft){
		handSprite.setPosition(sprite.getPosition().x - 5, sprite.getPosition().y);
		
	}
	else{
		handSprite.setPosition(sprite.getPosition().x + 5, sprite.getPosition().y);
		
	}
	
}
void Gun::updateCursor(){
	mousePos = Controls::get()->getmousepos;
}
void Gun::draw(){
	window.draw(handSprite);
}