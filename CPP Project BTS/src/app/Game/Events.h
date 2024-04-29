#pragma once

#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>

namespace APP {

	/// <summary>
	/// Classe qui g�re les �v�nements
	/// </summary>
	class Event {
	public:

		// Type de fonction sans param�tre
		using Function = std::function<void()>;

		// Type de fonctions pour les touches du clavier
		using KeyFunction = std::function<void(sf::Keyboard::Key)>;
		using TextFunction = std::function<void(sf::Uint32)>;

		// Liste des fonctions � appeler
		static std::vector<Function> onClick;
		static std::vector<Function> onHover;
		static std::vector<Function> onUnhover;
		static std::vector<KeyFunction> onKey;
		static std::vector<TextFunction> onTextEntered;

		// Met � jour les �v�nements
		static void processEvents(sf::RenderWindow& window);

		// Ajoute une fonction � appeler
		static void addOnClick(Function function);
		static void addOnHover(Function function);
		static void addOnUnhover(Function function);
		static void addOnKey(KeyFunction function);
		static void addOnTextEntered(TextFunction function);

		// Appelle les fonctions enregistr�es
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