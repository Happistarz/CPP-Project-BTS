#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../Helper/Functions.h"
#include "../Game/Events.h"
#include "Button.h"
#include "TextInput.h"

namespace UI {
	/// <summary>
	/// Classe modal qui permet d'afficher une fenetre modale
	/// </summary>
	class Modal {
	private:
		// Elements graphiques
		sf::RectangleShape background;
		sf::RenderWindow& window;
		
		// Elements de texte
		sf::Text title;
		sf::Font& font;
		
		bool opened;


		// Elements de la fenetre
		UI::Button* closeButton;
		UI::Button* submitButton;
		UI::TextInput* textInput;

		// Callback
		using onSubmit = std::function<void(std::string)>;
		onSubmit onSubmitCallback;
	public:
		/// <summary>
		/// Constructeur de la classe modal
		/// </summary>
		/// <param name="position"></param>
		/// <param name="size"></param>
		/// <param name="title"></param>
		/// <param name="font"></param>
		/// <param name="window"></param>
		Modal(sf::Vector2f position, sf::Vector2f size, std::string title, sf::Font& font, sf::RenderWindow& window);

		/// <summary>
		/// Destructeur de la classe modal
		/// </summary>
		~Modal();

		/// <summary>
		/// Affiche la fenetre modale
		/// </summary>
		void draw();

		/// <summary>
		/// Met a jour la fenetre modale
		/// </summary>
		void update();

		/// <summary>
		/// Fonction pour ouvrir la fenetre modale
		/// </summary>
		void openModal();

		/// <summary>
		/// Fonction pour fermer la fenetre modale
		/// </summary>
		void closeModal();

		/// <summary>
		/// Ajoute un callback pour le bouton de validation
		/// </summary>
		/// <param name="callback"></param>
		void setCallback(onSubmit callback) { onSubmitCallback = callback; }
	};
}
