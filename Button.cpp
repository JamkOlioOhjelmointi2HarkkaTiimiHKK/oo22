#include "Button.h"


Button::Button(sf::Vector2f position, std::string text, std::function<void()> func)
{
	function = func;
	button.setPosition(position);
	button.setSize(sf::Vector2f(150, 150));
	button.setFillColor(sf::Color().Magenta);
	buttonText.setFont(Content::get()->font);
	buttonText.setString(text);
	buttonText.setPosition((position.x + button.getSize().x / 2 - buttonText.getGlobalBounds().width / 2),(position.y + button.getSize().y / 2 - buttonText.getGlobalBounds().height / 2));
}

void Button::draw()
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
