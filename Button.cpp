#include "Button.h"


Button::Button(sf::Vector2f position, std::string text, std::function<void()> func, sf::Vector2f size)
{
	initialize(position, func, size, text);
}

Button::Button(double x, double y, std::string text, std::function<void()> func, sf::Vector2f size)
{
	initialize(sf::Vector2f(x, y), func, size, text);
}

void Button::initialize(sf::Vector2f position, std::function<void()> func, sf::Vector2f size, std::string text){
	function = func;
	calibri = Content::get()->calibri;
	button.setPosition(position);
	button.setSize(size);
	button.setFillColor(sf::Color().Magenta);
	buttonText.setFont(calibri);
	buttonText.setString(text);
	buttonText.setPosition((position.x + button.getSize().x / 2 - buttonText.getGlobalBounds().width / 2), (position.y + button.getSize().y / 2 - buttonText.getGlobalBounds().height / 2));
}

void Button::draw(sf::RenderWindow &window)
{
	window.draw(button);
	window.draw(buttonText);
}

void Button::update()
{
	if (button.getGlobalBounds().contains(Controls::get()->getmousepos())){

		isMouseOverButton = true;

		if (Controls::get()->mIsReleased(sf::Mouse::Left)){
			function();
		}
	}
	else
		isMouseOverButton = false;
}

void Button::setSize(sf::Vector2f size){
	this->button.setSize(size);
}
void Button::setColor(sf::Color color){
	this->button.setFillColor(color);
}
void Button::setColor(int r, int g, int b){
	this->button.setFillColor(sf::Color(r, g, b));
}

Button::~Button()
{
}
