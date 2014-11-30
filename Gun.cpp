#include "Gun.h"

Gun::Gun(){

}
Gun::~Gun(){

}

void Gun::create(){
	this->handSprite.setTexture(Content::get()->gunHandTexture);
}

void Gun::update(sf::Sprite sprite){
	handSprite.setPosition(sprite.getPosition());
}

void Gun::draw(){
	window.draw(handSprite);
}