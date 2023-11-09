#pragma once

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../Reader/JsonReader.h"

namespace APP {
	/// <summary>
	/// Classe Game qui gere le jeu
	/// </summary>
	class Game {
	private:
		// json reader
		READER::JsonReader* jsonReader;
		// window
		sf::RenderWindow window;
		// root path
		std::string rootPath;
	public:
		/// <summary>
		/// Initialise le jeu et construit la fenetre
		/// </summary>
		/// <param name="rootPath"></param>
		/// <param name="jsonReader"></param>
		Game(std::string rootPath, READER::JsonReader* jsonReader);

		~Game();

		/// <summary>
		/// Lance la boucle de jeu
		/// </summary>
		void run();

		/// <summary>
		/// Recupere les evenements de la fenetre et les traite
		/// </summary>
		void processEvents();

		/// <summary>
		/// Recupere les entrees clavier et les traite
		/// </summary>
		void handleInput();

	};
}


#endif // !GAME_H