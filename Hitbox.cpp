#include "Hitbox.h"
Hitbox::Hitbox(){
	headHitbox.setFillColor(sf::Color(48, 48, 224, 192));
	bodyHitbox.setFillColor(sf::Color(224, 48, 48, 192));
	bodyLeftHitbox.setFillColor(sf::Color(224, 72, 72, 192));
	bodyRightHitbox.setFillColor(sf::Color(224, 24, 24, 192));
	legHitbox.setFillColor(sf::Color(48, 224, 48, 192));
	fullHitbox.setFillColor(sf::Color(224, 48, 224, 192));
}
Hitbox::~Hitbox(){

}
void Hitbox::initializeHitBoxes(sf::Sprite sprite, float sizeX, float sizeY, bool isPlayer){
	this->isPlayer = isPlayer;
	
	if (isPlayer){
		headHitbox.setSize(sf::Vector2f(sizeX - 10, 7));
		headHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 5, sprite.getPosition().y - sprite.getOrigin().y);

		bodyHitbox.setSize(sf::Vector2f(sizeX, sizeY - 14));
		bodyHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + 7);

		bodyLeftHitbox.setSize(sf::Vector2f(sizeX / 2, sizeY - 14));
		bodyLeftHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + 7);

		bodyRightHitbox.setSize(sf::Vector2f(sizeX / 2, sizeY - 14));
		bodyRightHitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getOrigin().y + 7);

		legHitbox.setSize(sf::Vector2f(sizeX - 6, 7));
		legHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 3, sprite.getPosition().y + (sprite.getOrigin().y - 7));
	}
	
	else{
		fullHitbox.setSize(sf::Vector2f(sizeX, sizeY));
		fullHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y);
	}
	
}
void Hitbox::update(sf::Sprite sprite){
	if (isPlayer){
		headHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 5, sprite.getPosition().y - sprite.getOrigin().y);
		bodyHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + 7);
		bodyLeftHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + 7);
		bodyRightHitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getOrigin().y + 7);
		legHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 3, sprite.getPosition().y + (sprite.getOrigin().y - 7));
	}
	else{
		fullHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y);
	}
	
}
void Hitbox::draw(){
	if (isPlayer){
		window.draw(legHitbox);
		window.draw(bodyHitbox);
		window.draw(headHitbox);
		window.draw(bodyLeftHitbox);
		window.draw(bodyRightHitbox);
	}
	else{
		window.draw(fullHitbox);
	}
}