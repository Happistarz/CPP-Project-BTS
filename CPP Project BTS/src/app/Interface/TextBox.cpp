#include "TextBox.h"

namespace UI {
	TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font, unsigned int fontSize, sf::RenderWindow& window)
		: background(), text(), clicked(false), hovered(false), window(window), lastHovered(false)
	{
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

	void TextBox::update(sf::RenderWindow& window) {
		// recupere la position de la souris
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		// verifie si la souris est sur le bouton
		hovered = background.getGlobalBounds().contains(mousePos) ? true : false;

		if (hovered) {

			hovered = true;

			// verifie si le bouton est clique et si le callback n'a pas deja ete appele et hover est true
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !clicked) {
				OnClick();
				clicked = true;
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				clicked = false;
			}
		}
		else {
			hovered = false;
		}

		// verifie si le bouton a ete hover ou unhover
		if (hovered != lastHovered) {
			if (hovered) {
				OnHover();
			}
			else {
				OnUnHover();
			}
		}

		// met a jour la derniere position de la souris
		lastHovered = hovered;
	}

	void TextBox::draw(sf::RenderWindow& window) {
		// affiche le background et le texte
		window.draw(background);
		window.draw(text);
	}

	void TextBox::changeLocalTextPosition(sf::Vector2f offset) {
		text.setPosition(
			background.getPosition() + text.getGlobalBounds().getSize() / 2.f + offset
		);
	}

	void TextBox::centerText() {
		HELPER::centerText(text, background.getSize(), background.getPosition());
	}
}