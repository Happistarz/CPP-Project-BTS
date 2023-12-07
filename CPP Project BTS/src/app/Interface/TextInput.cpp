#include "TextInput.h"

int cursorcount = CONSTANT::CURSOR_FRAME_COUNT;

namespace UI {
	TextInput::TextInput(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string _text, unsigned int characterSize, sf::RenderWindow& window)
		: TextBox(position, size, "", font, characterSize, window), window(window), focused(false), cursor(), placeholder(), textBuffer(), cursorindex(0), maxTextSize(size.x / characterSize)
	{
		background.setSize(sf::Vector2f(size.x, text.getGlobalBounds().height + 40.f));

		textBuffer.reserve(100);

		cursor.setSize(sf::Vector2f(2.f, background.getGlobalBounds().height - 10.f));
		cursor.setFillColor(sf::Color::White);


		setOutlineColor(sf::Color::White);
		setShapeColor(CONSTANT::BUTTON_NORMAL_COLOR);
		setTextColor(sf::Color::White);

		changeLocalTextPosition(sf::Vector2f(5.f, 4.f));

		cursor.setPosition(
			text.findCharacterPos(cursorindex) + sf::Vector2f(0.f, 2.f)
		);

		placeholder.setFont(font);
		placeholder.setCharacterSize(characterSize);
		placeholder.setFillColor(sf::Color(50, 50, 50));
		placeholder.setString(_text);
		placeholder.setPosition(text.getPosition());

		// ajout des events
		APP::Event::addOnTextEntered(std::bind(&TextInput::OnTextEntered, this, std::placeholders::_1));
		APP::Event::addOnKey(std::bind(&TextInput::OnKeyPressed, this, std::placeholders::_1));
		APP::Event::addOnClick(std::bind(&TextInput::OnGlobalClick, this));
	}

	TextInput::~TextInput()
	{
	}


	void TextInput::draw()
	{
		TextBox::draw(window);
		// si le text est vide on affiche le placeholder
		if (textBuffer.size() == 0) {
			window.draw(placeholder);
		}
		// si focus on affiche le curseur et on le fait clignoter
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

	void TextInput::OnGlobalClick()
	{
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		if (!background.getGlobalBounds().contains(mousePos)) {
			focused = false;
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
		// si focus on ajoute le caractere au buffer
		if (focused) {
			// si backspace on supprime le dernier caractere
			if (unicode == 8) {
				if (textBuffer.size() > 0) {
					textBuffer.pop_back();
					cursorindex--;
				}
			}
			// si enter on quitte le focus
			else if (unicode == 13) {
				focused = false;
			}
			// sinon on ajoute le caractere
			else {
				textBuffer.insert(textBuffer.begin() + cursorindex, static_cast<char>(unicode));
				cursorindex++;
			}
		}

		int start = 0;
		for (int i = textBuffer.size() - 1; i >= 0; i--) {
			setText(std::string(textBuffer.begin() + i, textBuffer.end()));
			if (text.getLocalBounds().width > background.getSize().x) {
				start = i + 1;
				break;
			}
		}

		// Mettez à jour le texte affiché et la position du curseur
		setText(GetText(start));


		// on deplace le curseur
		cursor.setPosition(
			text.findCharacterPos(cursorindex) + sf::Vector2f(0.f, 2.f)
		);
	}

	void TextInput::OnKeyPressed(sf::Keyboard::Key key) {
		// si focus on gere les fleches
		if (focused) {
			if (key == sf::Keyboard::Left) {
				if (cursorindex > 0) {
					cursorindex--;
				}
			}
			else if (key == sf::Keyboard::Right) {
				if (cursorindex < textBuffer.size()) {
					cursorindex++;
				}
			}
		}

		// on deplace le curseur
		cursor.setPosition(
			text.findCharacterPos(cursorindex) + sf::Vector2f(0.f, 2.f)
		);
	}

	std::string TextInput::GetText(int start) {
		std::string textString = "";
		for (int i = start; i < textBuffer.size(); i++) {
			textString += textBuffer[i];
		}
		return textString;
	}
}