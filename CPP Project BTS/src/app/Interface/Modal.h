#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../Helper/Functions.h"
#include "../Game/Events.h"
#include "Button.h"
#include "TextInput.h"

namespace UI {
	class Modal {
	private:
		sf::RectangleShape background;
		sf::Text title;
		UI::Button* closeButton;
		sf::RenderWindow& window;
		sf::Font& font;

		bool opened;

		UI::Button* submitButton;
		UI::TextInput* textInput;

		using onSubmit = std::function<void(std::string)>;
		onSubmit onSubmitCallback;
	public:
		Modal(sf::Vector2f position, sf::Vector2f size, std::string title, sf::Font& font, sf::RenderWindow& window);
		~Modal();

		void draw();
		void update();

		void openModal();
		void closeModal();

		void setCallback(onSubmit callback) { onSubmitCallback = callback; }
	};
}
