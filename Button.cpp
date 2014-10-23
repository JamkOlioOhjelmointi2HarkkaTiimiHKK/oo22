#include "Button.h"


Button::Button(sf::Vector2f position, std::string text, std::function<void()> func)
{
	function = func;
	calibri = Content::get()->getCalibriFont();
	button.setPosition(position);
	button.setSize(sf::Vector2f(150, 150));
	button.setFillColor(sf::Color().Magenta);
	buttonText.setFont(calibri);
	buttonText.setString(text);
	buttonText.setPosition((position.x + button.getSize().x / 2 - buttonText.getGlobalBounds().width / 2),(position.y + button.getSize().y / 2 - buttonText.getGlobalBounds().height / 2));
}

Button::Button(double x, double y, std::string text, std::function<void()> func)
{
	function = func;
	calibri = Content::get()->getCalibriFont();
	button.setPosition(x, y);
	button.setSize(sf::Vector2f(150, 150));
	button.setFillColor(sf::Color().Magenta);
	buttonText.setFont(calibri);
	buttonText.setString(text);
	buttonText.setPosition((x + button.getSize().x / 2 - buttonText.getGlobalBounds().width / 2), (y + button.getSize().y / 2 - buttonText.getGlobalBounds().height / 2));
}

void Button::draw(sf::RenderWindow &window)
{
	window.draw(button);
	window.draw(buttonText);
}

void Button::update()
{
	if (Controls::get()->mIsReleased(sf::Mouse::Left) && button.getGlobalBounds().contains(Controls::get()->getmousepos()))
	{
		function();
	}
}

Button::~Button()
{
}
