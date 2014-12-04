#include "Button.h"


Button::Button(sf::Vector2f position, std::string text, std::function<void()> func, sf::Vector2f size)
{
	initialize(position, func, size, text);
}

Button::Button(double x, double y, std::string text, std::function<void()> func, sf::Vector2f size)
{
	initialize(sf::Vector2f(x, y), func, size, text);
}

Button::Button(sf::Vector2f position, std::function<void()> func, sf::Vector2f size, std::string text)
{
	initialize(position, func, size, text);
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

//editor
Button::Button(sf::Vector2f size, sf::Vector2f position, std::string text, std::function<void()> func)
{
	function = func;
	button.setPosition(position);
	button.setSize(size);
	button.setFillColor(sf::Color().Magenta);
	buttonText.setFont(Content::get()->font);
	buttonText.setString(text);
	buttonText.setPosition((position.x + button.getSize().x / 2 - buttonText.getGlobalBounds().width / 2), (position.y + button.getSize().y / 2 - buttonText.getGlobalBounds().height / 2));
}

void Button::draw(sf::RenderWindow &window)
{
	window.draw(button);
	window.draw(buttonText);
}

void Button::draw()
{
	window.draw(button);
	window.draw(buttonText);
}

void Button::update()
{
	// Jos nappia painetaan, suoritetaan funktio
	if (Controls::get()->mIsReleased(sf::Mouse::Left) && button.getGlobalBounds().contains(Controls::get()->getmousepos()))
	{
		function();
	}
		
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
