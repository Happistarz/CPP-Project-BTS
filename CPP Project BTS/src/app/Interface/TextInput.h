#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "TextBox.h"
#include "../Game/Constants.h"
#include "../Game/Events.h"

namespace UI {
	/// <summary>
	/// Text input box pour l'entrée de texte
	/// </summary>
	class TextInput : public TextBox
	{
	public:
		/// <summary>
		/// Constructeur
		/// </summary>
		/// <param name="position"></param>
		/// <param name="size"></param>
		/// <param name="font"></param>
		/// <param name="_text"></param>
		/// <param name="characterSize"></param>
		/// <param name="window"></param>
		TextInput(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string _text, unsigned int characterSize, sf::RenderWindow& window);

		/// <summary>
		/// Destructeur
		/// </summary>
		~TextInput();

		/// <summary>
		/// Affichage des éléments
		/// </summary>
		void draw();

		/// <summary>
		/// Evenements on click
		/// </summary>
		void OnClick() override;

		/// <summary>
		/// Evenements on global click
		/// </summary>
		void OnGlobalClick();

		/// <summary>
		/// Evenements on hover
		/// </summary>
		void OnHover() override;

		/// <summary>
		/// Evenements on unhover
		/// </summary>
		void OnUnHover() override;

		/// <summary>
		/// Evenements on text entered
		/// </summary>
		/// <param name="unicode"></param>
		void OnTextEntered(sf::Uint32 unicode);

		/// <summary>
		/// Evenements on key pressed
		/// </summary>
		/// <param name="key"></param>
		void OnKeyPressed(sf::Keyboard::Key key);

		/// <summary>
		/// Set le texte
		/// </summary>
		/// <param name="_text"></param>
		void SetText(std::string _text) { text.setString(_text); }

		/// <summary>
		/// Get le texte
		/// </summary>
		/// <returns></returns>
		std::string GetText(int start);

		/// <summary>
		/// Reset le texte et le buffer
		/// </summary>
		void reset() { text.setString(""); cursor.setPosition(sf::Vector2f(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y)); textBuffer.clear(); }

		/// <summary>
		/// Set le focus
		/// </summary>
		/// <param name="_focused"></param>
		void SetFocused(bool _focused) { focused = _focused; }

		/// <summary>
		/// Get le focus
		/// </summary>
		/// <returns></returns>
		bool GetFocused() { return focused; }

	private:
		// focus
		bool focused;

		// buffer de char
		std::vector<char> textBuffer;

		//placeholder pour afficher un texte d'aide
		sf::Text placeholder;

		// curseur
		sf::RectangleShape cursor;
		
		// window
		sf::RenderWindow& window;

		// index du curseur
		int cursorindex;

		// taille max du texte
		int maxTextSize;
	};
}