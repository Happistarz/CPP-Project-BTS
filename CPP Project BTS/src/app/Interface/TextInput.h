#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "TextBox.h"
#include "../Game/Constants.h"
#include "../Game/Events.h"

namespace UI {
	class TextInput : public TextBox
	{
	public:
		TextInput(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string _text, unsigned int characterSize, sf::RenderWindow& window);
		~TextInput();

		void draw();

		void OnClick() override;
		void OnHover() override;
		void OnUnHover() override;
		void OnTextEntered(sf::Uint32 unicode);
		void OnKeyPressed(sf::Keyboard::Key key);

		void SetText(std::string _text) { text.setString(_text); }
		std::string GetText() { return text.getString(); }

		void reset() { text.setString(""); cursor.setPosition(sf::Vector2f(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y)); textBuffer.clear(); }

		bool GetFocused() { return focused; }

	private:
		bool focused;
		std::vector<char> textBuffer;
		sf::Text placeholder;
		sf::RectangleShape cursor;
		sf::RenderWindow& window;
	};
}