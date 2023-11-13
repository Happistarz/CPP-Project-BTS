#pragma once
#ifndef SATELLITERENDER_H
#define SATELLITERENDER_H

#include <SFML/Graphics.hpp>
#include "../../Helper/Functions.h"

namespace GRAPHICS {
	class SatelliteRender {
	private:
		sf::RectangleShape background;
		sf::RectangleShape satelliteBox;
	public:
		SatelliteRender(sf::RenderWindow& window);
		~SatelliteRender();

		void draw(sf::RenderWindow& window);
	};
}

#endif // !SATELLITERENDER_H
