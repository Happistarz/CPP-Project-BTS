#include "TextInput.h"

int cursorcount = CONSTANT::CURSOR_FRAME_COUNT;

namespace UI {
	TextInput::TextInput(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string _text, unsigned int characterSize, sf::RenderWindow& window)
		: TextBox(position, size, "", font, characterSize, window), window(window), focused(false)
	{
		background.setSize(sf::Vector2f(size.x, text.getGlobalBounds().height+40.f));

		textBuffer.reserve(100);

		cursor.setSize(sf::Vector2f(2.f, background.getGlobalBounds().height - 20.f));
		cursor.setFillColor(sf::Color::White);
		cursor.setPosition(position.x + 5.f, position.y + 5.f);

		cursor.setPosition(
			HELPER::getYShapePosition(
				background.getPosition(),
				background.getSize(),
				cursor.getSize()
			) + sf::Vector2f(5.f, 0.f)
		);

		setOutlineColor(sf::Color::White);
		setShapeColor(CONSTANT::BUTTON_NORMAL_COLOR);
		setTextColor(sf::Color::White);
		// change la position du texte pour qu'il soit au milieu gauche du textbox
		changeLocalTextPosition(sf::Vector2f(5.f, 0.f));

		placeholder.setFont(font);
		placeholder.setCharacterSize(characterSize);
		placeholder.setFillColor(sf::Color(50, 50, 50));
		placeholder.setString(_text);
		placeholder.setPosition(text.getPosition());

		APP::Event::addOnTextEntered(std::bind(&TextInput::OnTextEntered, this, std::placeholders::_1));
		APP::Event::addOnKey(std::bind(&TextInput::OnKeyPressed, this, std::placeholders::_1));
	}

	TextInput::~TextInput()
	{
	}


	void TextInput::draw()
	{
		TextBox::draw(window);
		if (textBuffer.size() == 0) {
			window.draw(placeholder);
		}
		if (focused) {
			if (cursorcount < 30) {
				cursor.setFillColor(sf::Color(255, 255, 255, cursorcount * 8.5f));
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

	void TextInput::OnTextEntered(sf::Uint32 unicode) {
		if (focused) {
			if (unicode == 8) {
				if (textBuffer.size() > 0) {
					textBuffer.pop_back();
				}
			}
			else if (unicode == 13) {
				focused = false;
			}
			else {
				textBuffer.push_back(static_cast<char>(unicode));
			}
		}

		std::string textString = "";
		for (auto& c : textBuffer) {
			textString += c;
		}
		setText(textString);
	}

	void TextInput::OnKeyPressed(sf::Keyboard::Key key) {
		if (focused) {
			switch (key) {
			case sf::Keyboard::Left:
				if (cursorcount > 0) {
					cursorcount--;
				}
				break;
			case sf::Keyboard::Right:
				if (cursorcount < textBuffer.size()) {
					cursorcount++;
				}
				break;
			default:
				break;
			}
		}

		cursor.setPosition(
			HELPER::getYShapePosition(
				background.getPosition(),
				background.getSize(),
				cursor.getSize()
			) + sf::Vector2f(text.getGlobalBounds().width, 0.f)
		);
	}
}