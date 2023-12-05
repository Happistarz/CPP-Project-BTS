#pragma once

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <thread>
#include "../Reader/JsonReader.h"
#include "Graphics/Simulator.h"
#include "Graphics/StationRender.h"
#include "Graphics/SatelliteRender.h"
#include "../Interface/Button.h"
#include "../Interface/TextInput.h"
#include "../Interface/Modal.h"
#include "Events.h"

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

		/// <summary>
		/// Detruit le jeu
		/// </summary>
		~Game();

		/// <summary>
		/// Lance la boucle de jeu
		/// </summary>
		void run();

		/// <summary>
		/// Lance un test
		/// </summary>
		void runTest();
	};
}


#endif // !GAME_H