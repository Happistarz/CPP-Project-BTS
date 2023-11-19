#pragma once
#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <SFML/Graphics.hpp>
#include "../../Helper/Functions.h"
#include "../../Reader/JsonReader.h"

namespace GRAPHICS {
	class Simulator {
	private:
		sf::RectangleShape sky;

		sf::Texture earthTexture;
		sf::Sprite earth;

		sf::Texture satelliteTexture;
		sf::Sprite satellite;
		sf::CircleShape satelliteOrbit;

		sf::Texture stationTexture;
		sf::Sprite station;

		sf::RectangleShape debug;
	public:
		Simulator(sf::RenderWindow& window, std::string& root, READER::JsonReader& jsonReader);
		~Simulator();

		void update(float deltaTime);
		void draw(sf::RenderWindow& window);
	};
}
#endif
