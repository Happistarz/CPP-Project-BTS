#include "TextBox.h"

namespace UI {
	TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font, unsigned int fontSize, sf::RenderWindow& window) {
		// init le background
		background.setPosition(position);
		background.setSize(size);
		background.setFillColor(sf::Color::White);

		// init le texte
		this->text.setString(text);
		this->text.setCharacterSize(fontSize);
		this->text.setFillColor(sf::Color::Black);
		this->text.setFont(font);
		// centre le texte
		HELPER::centerText(this->text, size, position);
	}

	TextBox::~TextBox() {
	}

	void TextBox::draw(sf::RenderWindow& window) {
		window.draw(background);
		window.draw(text);
	}
}