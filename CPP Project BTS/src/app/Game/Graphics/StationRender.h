#pragma once

#ifndef STATIONRENDER_H
#define STATIONRENDER_H

#include <SFML/Graphics.hpp>
#include "../../Helper/Functions.h"

namespace GRAPHICS {
	class StationRender {
	private:
		sf::RectangleShape background;
		sf::RectangleShape stationBox;
	public:
		StationRender(sf::RenderWindow& window);
		~StationRender();

		void draw(sf::RenderWindow& window);
	};
}

#endif // !STATIONRENDER_H

