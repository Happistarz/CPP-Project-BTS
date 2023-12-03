#pragma once

#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>
#include <SFML/Graphics.hpp>


namespace CONSTANT {

	// COMMUNICABLE RENDERING
	const unsigned int charSize = 20U;
	const unsigned int LOGLINECOUNT = 10U;
	const unsigned int LOGLINESIZE = 25U;

	const sf::Vector2f BUTTON_SIZE = sf::Vector2f(175.f, 50.f);
	const sf::Vector2f TEXTBOX_SIZE = sf::Vector2f(150.f, 50.f);
	const sf::Vector2f LOG_SIZE = sf::Vector2f(charSize * LOGLINESIZE + 10.f, charSize * LOGLINECOUNT + 10.f);

	const sf::Color CONNECTED_COLOR = sf::Color(0, 255, 0);
	const sf::Color DISCONNECTED_COLOR = sf::Color(255, 0, 0);

	const sf::Color BUTTON_NORMAL_COLOR = sf::Color(77, 166, 255);
	const sf::Color BUTTON_HOVER_COLOR = sf::Color(128, 191, 255);

	const sf::Color TEXTINPUT_NORMAL_COLOR = sf::Color(255, 255, 255);
	const sf::Color TEXTINPUT_HOVER_COLOR = sf::Color(100, 100, 100);

	const int CURSOR_FRAME_COUNT = 30;
}

#endif // !CONSTANT_H