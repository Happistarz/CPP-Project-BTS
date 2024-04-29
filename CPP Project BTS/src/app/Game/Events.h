#pragma once

#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>

namespace APP {

	/// <summary>
	/// Classe qui gère les événements
	/// </summary>
	class Event {
	public:

		// Type de fonction sans paramètre
		using Function = std::function<void()>;

		// Type de fonctions pour les touches du clavier
		using KeyFunction = std::function<void(sf::Keyboard::Key)>;
		using TextFunction = std::function<void(sf::Uint32)>;

		// Liste des fonctions à appeler
		static std::vector<Function> onClick;
		static std::vector<Function> onHover;
		static std::vector<Function> onUnhover;
		static std::vector<KeyFunction> onKey;
		static std::vector<TextFunction> onTextEntered;

		// Met à jour les événements
		static void processEvents(sf::RenderWindow& window);

		// Ajoute une fonction à appeler
		static void addOnClick(Function function);
		static void addOnHover(Function function);
		static void addOnUnhover(Function function);
		static void addOnKey(KeyFunction function);
		static void addOnTextEntered(TextFunction function);

		// Appelle les fonctions enregistrées
		static void callOnClick();
		static void callOnHover();
		static void callOnUnhover();
		static void callOnKey(sf::Keyboard::Key key);
		static void callOnTextEntered(sf::Uint32 unicode);

	private:

		// Retourne l'instance de la classe
		static Event& getInstance();
	};
}