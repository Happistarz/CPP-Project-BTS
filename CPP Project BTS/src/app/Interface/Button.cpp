#include "Button.h"


sf::Color NORMAL_COLOR = sf::Color(77, 166, 255);
sf::Color HOVER_COLOR = sf::Color(128, 191, 255);

namespace UI {
	Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string msg, sf::Font& font, unsigned short char_size, sf::RenderWindow& window, Callback callback)
		: window(window), isHovered(false),
		onClickCallback(callback), isClicked(false),
		TextBox(pos, size, msg, font, char_size, window)
	{

		// init le bouton
		setShapeColor(NORMAL_COLOR);

		// init le texte
		setTextColor(sf::Color::White);
	}

	Button::~Button()
	{
		// unset le callback
		onClickCallback = nullptr;

	}

	void Button::draw()
	{
		// affiche le bouton
		TextBox::draw(window);
	}

	void Button::update()
	{
		// recupere la position de la souris
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		// verifie si la souris est sur le bouton
		isHovered = background.getGlobalBounds().contains(mousePos) ? true : false;

		if (isHovered) {
			// si oui, change la couleur du bouton
			setShapeColor(HOVER_COLOR);

			// verifie si le bouton est clique et si le callback n'a pas deja ete appele et hover est true
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isClicked) {
				onClickCallback();
				isClicked = true;
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				isClicked = false;
			}
		}
		else {
			// si non, remet la couleur par defaut
			setShapeColor(NORMAL_COLOR);
		}
	}

}