#include "Hitbox.h"
Hitbox::Hitbox(){
	headHitbox.setFillColor(sf::Color(48, 48, 224, 192));
	bodyHitbox.setFillColor(sf::Color(224, 48, 48, 192));
	legHitbox.setFillColor(sf::Color(48, 224, 48, 192));
}
Hitbox::~Hitbox(){

}
void Hitbox::initializeHitBoxes(sf::Sprite sprite, float sizeX, float sizeY){
	
	headHitbox.setSize(sf::Vector2f(sizeX - 10, 7));
	headHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 5, sprite.getPosition().y - sprite.getOrigin().y);

	bodyHitbox.setSize(sf::Vector2f(sizeX, sizeY-14));
	bodyHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + 7);
	
	legHitbox.setSize(sf::Vector2f(sizeX - 6, 7));
	legHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 3, sprite.getPosition().y + (sprite.getOrigin().y - 7));
}
void Hitbox::update(sf::Sprite sprite){
	headHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 5, sprite.getPosition().y - sprite.getOrigin().y);
	bodyHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + 7);
	legHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 3, sprite.getPosition().y + (sprite.getOrigin().y - 7));
}
void Hitbox::draw(sf::RenderWindow &window){
	window.draw(legHitbox);
	window.draw(bodyHitbox);
	window.draw(headHitbox);
}