#pragma once
#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <SFML/Graphics.hpp>
#include "../../Helper/Functions.h"

namespace GRAPHICS {
	class Simulator {
	private:
		sf::RectangleShape sky;

		sf::Texture earthTexture;
		sf::Sprite earth;

		sf::Texture satelliteTexture;
		sf::Sprite satellite;

		sf::Texture stationTexture;
		sf::Sprite station;
	public:
		Simulator(sf::RenderWindow& window, std::string& root);
		~Simulator();

		void draw(sf::RenderWindow& window);
	};
}
#endif
