#include "Button.h"

namespace UI {
	Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string msg, unsigned short char_size, sf::RenderWindow& window) : window(window), isHovered(false)
	{
		shape.setPosition(pos);
		shape.setSize(size);
		shape.setFillColor(sf::Color(77, 166, 255));

		text.setString(msg);
		text.setCharacterSize(char_size);
		text.setPosition(
			HELPER::getShapePosition(
				pos,
				size,
				text.getScale()
			)
		);
	}

	Button::~Button()
	{
	}

	void Button::draw()
	{
		window.draw(shape);
		window.draw(text);
	}

	void Button::update()
	{
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		isHovered = shape.getGlobalBounds().contains(mousePos) ? true : false;

		shape.setFillColor(isHovered ? sf::Color(128,191,255) : sf::Color(77,166,255));

	}



}