#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "../Helper/Functions.h"
#include <SFML/Graphics.hpp>

namespace UI {
	class Button
	{
	private:
		bool isHovered;
		sf::RenderWindow& window;
		sf::RectangleShape shape;
		sf::Text text;
	public:
		Button(sf::Vector2f pos, sf::Vector2f size, std::string msg, unsigned short char_size, sf::RenderWindow& window);
		~Button();

		void draw();
		void update();
		bool isHover() const { return isHovered; }
	};
}

#endif
