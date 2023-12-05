#include "Modal.h"

namespace UI {
	Modal::Modal(sf::Vector2f position, sf::Vector2f size, std::string title, sf::Font& font, sf::RenderWindow& window)
		: background(), title(), window(window), font(font), opened(false), closeButton(nullptr), submitButton(nullptr), textInput(nullptr), onSubmitCallback(nullptr)
	{

		// init background
		background.setSize(size);
		background.setPosition(position);
		background.setFillColor(sf::Color(0,0,0,100));
		background.setOutlineColor(sf::Color::White);
		background.setOutlineThickness(2.f);

		// init close button
		sf::Vector2f closeSize = sf::Vector2f(30.f,30.f);
		closeButton = new UI::Button(
			sf::Vector2f(position.x + size.x - closeSize.x, position.y),
			sf::Vector2f(closeSize.x, closeSize.y),
			"X",
			font,
			20U,
			window,
			[&]() {
				closeModal(); 
			});

		// init title
		this->title.setFont(font);
		this->title.setCharacterSize(20U);
		this->title.setFillColor(sf::Color::White);
		this->title.setString(title);
		this->title.setPosition(position.x + 5.f, position.y + 5.f);

		sf::Vector2f submitSize = sf::Vector2f(200.f, 75.f);
		
		// init submit button
		submitButton = new UI::Button(
			sf::Vector2f(position.x + size.x - submitSize.x/2, position.y + size.y - submitSize.y/2),
			sf::Vector2f(submitSize.x/2, submitSize.y/2),
			"Submit",
			font,
			20U,
			window,
			[&]() { 
				if (onSubmitCallback != nullptr)
					if (textInput->GetText(0) != "")
						onSubmitCallback(textInput->GetText(0));
					else 
						onSubmitCallback("Default");
				closeModal(); 
		});

		// init text input
		textInput = new UI::TextInput(
			HELPER::getShapePosition(
				background.getPosition(),
				background.getSize(),
				submitButton->getShape().getSize()
			),
			sf::Vector2f(submitSize.x, submitSize.y),
			font,
			"Message...",
			20U,
			window
		);
	}

	Modal::~Modal()
	{
		// delete les pointeurs
		delete closeButton;
		delete submitButton;
		delete textInput;
	}

	void Modal::draw()
	{
		// si le modal est ouvert, on affiche tout
		if (opened) {
			window.draw(background);
			window.draw(title);
			closeButton->draw();
			submitButton->draw();
			textInput->draw();
		}
	}

	void Modal::update()
	{
		// si le modal est ouvert, on update tout
		if (opened) {
			closeButton->update(window);
			submitButton->update(window);
			textInput->update(window);
		}
	}

	void Modal::openModal()
	{
		// on reset le text input et on le focus
		opened = true;
		textInput->reset();
		textInput->SetFocused(true);
	}

	void Modal::closeModal()
	{
		// on reset le text input et on le defocus
		opened = false;
		textInput->reset();
		textInput->SetFocused(false);
	}
}
