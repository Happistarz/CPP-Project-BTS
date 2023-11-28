#pragma once
#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <SFML/Graphics.hpp>
#include "../../Helper/Functions.h"
#include "../../Reader/JsonReader.h"

namespace GRAPHICS {
	/// <summary>
	/// Simulator qui gere la simulation du satellite, de la station et de la terre
	/// </summary>
	class Simulator {
	private:
		// Les formes

		// sky
		sf::RectangleShape sky;

		// earth
		sf::Texture earthTexture;
		sf::Sprite earth;

		// satellite
		sf::Texture satelliteTexture;
		sf::Sprite satellite;
		sf::CircleShape satelliteOrbit;

		// station
		sf::Texture stationTexture;
		sf::Sprite station;

		// line connection
		sf::RectangleShape lineConnection;
		bool drawLineConnection;

		// debug
		sf::RectangleShape debug;
	public:

		/// <summary>
		/// Constructeur du simulator
		/// </summary>
		/// <param name="window"></param>
		/// <param name="root"></param>
		/// <param name="jsonReader"></param>
		Simulator(sf::RenderWindow& window, std::string& root, READER::JsonReader& jsonReader);

		/// <summary>
		/// Destructeur du simulator
		/// </summary>
		~Simulator();

		/// <summary>
		/// Update le simulator pour bouger les objets
		/// </summary>
		/// <param name="deltaTime"></param>
		void update(float deltaTime);

		/// <summary>
		/// Affiche les formes
		/// </summary>
		/// <param name="window"></param>
		void draw(sf::RenderWindow& window);

		/// <summary>
		/// Set si on doit afficher la ligne de connexion
		/// </summary>
		/// <param name="drawLineConnection"></param>
		void setDrawLineConnection(bool drawLineConnection) { this->drawLineConnection = drawLineConnection; }
	};
}
#endif
