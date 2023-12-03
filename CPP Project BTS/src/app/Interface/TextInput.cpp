#include "TextInput.h"

int cursorcount = CONSTANT::CURSOR_FRAME_COUNT;

namespace UI {
	TextInput::TextInput(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string _text, unsigned int characterSize, sf::RenderWindow& window)
		: TextBox(position, size, "aaa", font, characterSize, window), window(window), focused(false)
	{
		textBuffer.reserve(100);

		cursor.setSize(sf::Vector2f(2.f, size.y - 20.f));
		cursor.setFillColor(sf::Color::White);
		cursor.setPosition(position.x + 5.f, position.y + 5.f);

		setOutlineColor(sf::Color::White);
		setShapeColor(CONSTANT::BUTTON_NORMAL_COLOR);
		setTextColor(sf::Color::White);
		// change la position du texte pour qu'il soit au milieu gauche du textbox
		changeGlobalTextPosition(
			HELPER::getYShapePosition(
				background.getPosition(),
				background.getSize(),
				text.getGlobalBounds().getSize()
			) + sf::Vector2f(5.f, 0.f)
		);

		placeholder.setFont(font);
		placeholder.setCharacterSize(characterSize);
		placeholder.setFillColor(sf::Color(50, 50, 50));
		placeholder.setString(_text);
		placeholder.setPosition(text.getPosition());

		APP::Event::addOnKey(std::bind(&TextInput::OnKeyPressed, this, std::placeholders::_1));
	}

	TextInput::~TextInput()
	{
	}


	void TextInput::draw()
	{
		TextBox::draw(window);
		/*if (textBuffer.size() == 0) {
			window.draw(placeholder);
		}*/
		if (focused) {
			if (cursorcount < 30) {
				window.draw(cursor);
				cursorcount++;
			}
			else if (cursorcount < CONSTANT::CURSOR_FRAME_COUNT * 2) {
				cursorcount++;
			}
			else {
				cursorcount = 0;
			}
		}
	}

	void TextInput::OnClick()
	{
		focused = true;
	}

	void TextInput::OnHover()
	{
		setOutlineColor(CONSTANT::TEXTINPUT_HOVER_COLOR);
		hovered = true;
	}

	void TextInput::OnUnHover()
	{
		setOutlineColor(sf::Color::White);
		hovered = false;
	}

	void TextInput::OnKeyPressed(sf::Keyboard::Key key) {
		if (focused) {
			if (key == sf::Keyboard::BackSpace) {
				if (textBuffer.size() > 0) {
					textBuffer.pop_back();
					text.setString(textBuffer.data());
				}
			}
			else if (key == sf::Keyboard::Return) {
				focused = false;
			}
			else {
				textBuffer.push_back(static_cast<char>(key));
				text.setString(textBuffer.data());
			}
		}
	}
}