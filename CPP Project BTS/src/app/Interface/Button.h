#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "../Helper/Functions.h"
#include "TextBox.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include "../Game/Constants.h"

namespace UI {

	/// <summary>
	/// Classe Button qui hérite de TextBox
	/// </summary>
	class Button : public TextBox
	{
	private:

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
		/// Evenement quand le bouton est cliqué
		/// </summary>
		void OnClick() override;

		/// <summary>
		/// Evenement quand le bouton est hover
		/// </summary>
		void OnHover() override;

		/// <summary>
		/// Evenement quand le bouton n'est plus hover
		/// </summary>
		void OnUnHover() override;
	};
}

#endif
