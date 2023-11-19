#pragma once

#include <SFML/Graphics.hpp>
#include "../Helper/Functions.h"

namespace UI {
	/// <summary>
	/// Textbox class for displaying text in a box
	/// </summary>
	class TextBox {
	protected:
		// les elements graphiques
		sf::RectangleShape background;
		sf::Text text;
	public:
		/// <summary>
		/// Constructor qui initialise les elements graphiques
		/// </summary>
		/// <param name="position"></param>
		/// <param name="size"></param>
		/// <param name="text"></param>
		/// <param name="font"></param>
		/// <param name="fontSize"></param>
		/// <param name="window"></param>
		TextBox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font, unsigned int fontSize, sf::RenderWindow& window);
		/// <summary>
		/// Destructor
		/// </summary>
		~TextBox();

		/// <summary>
		/// Draw le textbox
		/// </summary>
		/// <param name="window"></param>
		void draw(sf::RenderWindow& window);
		/// <summary>
		/// Set la couleur du text
		/// </summary>
		/// <param name="color"></param>
		void setTextColor(sf::Color color) { text.setFillColor(color); }
		/// <summary>
		/// Set la couleur du background
		/// </summary>
		/// <param name="color"></param>
		void setShapeColor(sf::Color color) { background.setFillColor(color); }
	};
}


