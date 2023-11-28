#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "../Helper/Functions.h"
#include "TextBox.h"
#include <SFML/Graphics.hpp>
#include <functional>

namespace UI {

	class Button : public TextBox
	{
	private:
		// isHovered = true si la souris est sur le bouton
		bool isHovered;
		// isClicked = true si le bouton est cliqué
		bool isClicked;

		// la fenetre sur laquelle le bouton est affiché
		sf::RenderWindow& window;

		// la fonction à appeler quand le bouton est cliqué
		using Callback = std::function<void()>;
		Callback onClickCallback;
	public:
		/// <summary>
		/// Init la position, la taille, le texte, la police, la taille du texte, la fenetre et la fonction à appeler quand le bouton est cliqué
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="size"></param>
		/// <param name="msg"></param>
		/// <param name="font"></param>
		/// <param name="char_size"></param>
		/// <param name="window"></param>
		/// <param name="callback"></param>
		Button(sf::Vector2f pos, sf::Vector2f size, std::string msg, sf::Font& font, unsigned short char_size, sf::RenderWindow& window, Callback callback);

		/// <summary>
		/// Destructeur
		/// </summary>
		~Button();

		/// <summary>
		/// Affiche le bouton
		/// </summary>
		void draw();

		/// <summary>
		/// Check si la souris est sur le bouton et si le bouton est cliqué
		/// </summary>
		void update();

		/// <summary>
		/// Renvoie true si le bouton est cliqué
		/// </summary>
		/// <returns></returns>
		bool isHover() const { return isHovered; }
	};
}

#endif
