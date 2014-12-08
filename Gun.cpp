#include "Gun.h"

Gun::Gun(){
	create();
}
Gun::~Gun(){

}

void Gun::create(){
	handSprite.setTexture(Content::get()->gunHandTexture);
	handSprite.setOrigin(5,0);
}

void Gun::update(sf::Sprite sprite){
	handSprite.setPosition(sprite.getPosition());
	handSprite.rotate(-1);
}

void Gun::draw(){
	window.draw(handSprite);
}