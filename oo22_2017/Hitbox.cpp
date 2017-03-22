#include "Hitbox.h"
Hitbox::Hitbox(){
	//Alustetaan havainnollistavia värejä hitboxeille.
	headHitbox.setFillColor(sf::Color(48, 48, 224, 192));
	bodyHitbox.setFillColor(sf::Color(224, 48, 48, 192));
	bodyLeftHitbox.setFillColor(sf::Color(224, 72, 72, 192));
	bodyRightHitbox.setFillColor(sf::Color(224, 24, 24, 192));
	legHitbox.setFillColor(sf::Color(48, 224, 48, 192));
	enemyBodyleftHitbox.setFillColor(sf::Color(224, 72, 72, 192));
	enemyBodyrightHitbox.setFillColor(sf::Color(224, 48, 224, 192));
	enemybodyHitbox.setFillColor(sf::Color(224, 48, 48, 192));
	enemyheadHitbox.setFillColor(sf::Color(48, 48, 224, 192));
	enemyLegHitbox.setFillColor(sf::Color(48, 224, 48, 192));
	legHeigh = 7;
}
Hitbox::~Hitbox(){

}
void Hitbox::initializeHitBoxes(sf::Sprite sprite, float sizeX, float sizeY, bool isPlayer){
	this->isPlayer = isPlayer;
	
	if (isPlayer){
		headHitbox.setSize(sf::Vector2f(sizeX - 10, legHeigh));
		headHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 5, sprite.getPosition().y - sprite.getOrigin().y);

		bodyHitbox.setSize(sf::Vector2f(sizeX, sizeY));
		bodyHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y);

		bodyLeftHitbox.setSize(sf::Vector2f(sizeX / 2, sizeY - 14));
		bodyLeftHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + legHeigh);

		bodyRightHitbox.setSize(sf::Vector2f(sizeX / 2, sizeY - 14));
		bodyRightHitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getOrigin().y + legHeigh);

		legHitbox.setSize(sf::Vector2f(sizeX - 6, legHeigh));
		legHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 3, sprite.getPosition().y + (sprite.getOrigin().y - legHeigh));
	}
	
	else{
		enemyBodyleftHitbox.setSize(sf::Vector2f(sizeX / 2, sizeY - 14));
		enemyBodyleftHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + legHeigh);

		enemyBodyrightHitbox.setSize(sf::Vector2f(sizeX / 2, sizeY - 14));
		enemyBodyrightHitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getOrigin().y + legHeigh);

		enemybodyHitbox.setSize(sf::Vector2f(sizeX, sizeY));
		enemybodyHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y);

		enemyheadHitbox.setSize(sf::Vector2f(sizeX - 10, legHeigh));
		enemyheadHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 5, sprite.getPosition().y - sprite.getOrigin().y);

		enemyLegHitbox.setSize(sf::Vector2f(sizeX - 10, legHeigh));
		enemyLegHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 3, sprite.getPosition().y + (sprite.getOrigin().y - legHeigh));
	}
	
}
void Hitbox::update(sf::Sprite sprite){
	if (isPlayer){
		headHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 5, sprite.getPosition().y - sprite.getOrigin().y);
		bodyHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y);
		bodyLeftHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + legHeigh);
		bodyRightHitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getOrigin().y + legHeigh);
		legHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 3, sprite.getPosition().y + (sprite.getOrigin().y - legHeigh));
	}
	else{
		enemyBodyleftHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y + legHeigh);
		enemyBodyrightHitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getOrigin().y + legHeigh);
		enemybodyHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y);
		enemyheadHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 5, sprite.getPosition().y - sprite.getOrigin().y);
		enemyLegHitbox.setPosition(sprite.getPosition().x - sprite.getOrigin().x + 3, sprite.getPosition().y + (sprite.getOrigin().y - legHeigh));
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
		window.draw(enemyBodyleftHitbox);
		window.draw(enemyBodyrightHitbox);
		window.draw(enemybodyHitbox);
		window.draw(enemyheadHitbox);
		window.draw(enemyLegHitbox);
	}
}