#include "Button.h"


namespace UI {
	Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string msg, sf::Font& font, unsigned short char_size, sf::RenderWindow& window, Callback callback)
		: onClickCallback(callback),
		TextBox(pos, size, msg, font, char_size, window)
	{

		// init le bouton
		setShapeColor(CONSTANT::BUTTON_NORMAL_COLOR);

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

	void Button::OnClick()
	{
		onClickCallback();
	}

	void Button::OnHover()
	{
		// change la couleur du bouton
		setShapeColor(CONSTANT::BUTTON_HOVER_COLOR);
	}

	void Button::OnUnHover()
	{
		// change la couleur du bouton
		setShapeColor(CONSTANT::BUTTON_NORMAL_COLOR);
	}

}