#pragma once
#ifndef SATELLITERENDER_H
#define SATELLITERENDER_H

#include <SFML/Graphics.hpp>
#include "../../Helper/Functions.h"
#include "../../Communication/Satellite.h"
#include "../../Interface/Button.h"
namespace GRAPHICS {
	class SatelliteRender {
	private:
		sf::RectangleShape background;
		sf::RectangleShape satelliteBox;
		UI::Button* ping;
		UI::Button* send;


		METIER::Satellite* satellite;
	public:
		SatelliteRender(sf::RenderWindow& window);
		~SatelliteRender();

		void draw(sf::RenderWindow& window);
	};
}

#endif // !SATELLITERENDER_H
