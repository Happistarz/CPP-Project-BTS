#pragma once

#include <SFML/Graphics.hpp>
#include "../Helper/Functions.h"

namespace UI {
	/// <summary>
	/// Textbox class pour creer des zones de textes
	/// </summary>
	class TextBox {
	private:
	protected:
		// les elements graphiques
		sf::RectangleShape background;
		sf::Text text;

		bool clicked;
		bool hovered;
		bool lastHovered;

		sf::RenderWindow& window;
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

		void update(sf::RenderWindow& window);
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

		/// <summary>
		/// Set le text
		/// </summary>
		/// <param name="text"></param>
		void setText(std::string text) { this->text.setString(text); }

		/// <summary>
		/// Ajoute une bordure de 2.f
		/// </summary>
		/// <param name="color"></param>
		void setOutlineColor(sf::Color color) { background.setOutlineColor(color); background.setOutlineThickness(2.f); }

		/// <summary>
		/// Change la position du text dans le textbox
		/// </summary>
		/// <param name="offset"></param>
		void changeLocalTextPosition(sf::Vector2f offset);

		/// <summary>
		/// Change la position du text dans la fenetre
		/// </summary>
		/// <param name="pos"></param>
		void changeGlobalTextPosition(sf::Vector2f pos) { text.setPosition(pos); }

		/// <summary>
		/// Retourne le rectangle du background
		/// </summary>
		/// <returns></returns>
		sf::RectangleShape getShape() { return background; }

		/// <summary>
		/// Centre le text dans le textbox
		/// </summary>
		void centerText();

		/// <summary>
		/// Fonction OnClick qui sera appelee quand le bouton sera clique
		/// </summary>
		virtual void OnClick() {};

		/// <summary>
		/// Fonction OnHover qui sera appelee quand la souris sera sur le bouton
		/// </summary>
		virtual void OnHover() {};

		/// <summary>
		/// Fonction OnUnHover qui sera appelee quand la souris ne sera plus sur le bouton
		/// </summary>
		virtual void OnUnHover() {};
	};
}


