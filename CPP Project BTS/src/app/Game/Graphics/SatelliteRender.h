#pragma once
#ifndef SATELLITERENDER_H
#define SATELLITERENDER_H

#include <SFML/Graphics.hpp>
#include "../../Helper/Functions.h"
#include "../../Communication/Satellite.h"
#include "../../Interface/Button.h"
#include "../../Interface/TextBox.h"
#include "../../Helper/LogDisplayer.h"

namespace GRAPHICS {
	class SatelliteRender {
	private:
		sf::RectangleShape background;
		sf::RectangleShape satelliteBox;
		UI::Button* ping;
		UI::Button* send;

		UI::TextBox* connect;
		UI::TextBox* log;
		HELPER::LogDisplayer* logDisplayer;

		sf::Text title;


		METIER::Satellite* satellite;
	public:
		SatelliteRender(sf::RenderWindow& window, sf::Font& font);
		~SatelliteRender();

		void draw(sf::RenderWindow& window);
		void update(float deltaTime);
		void pingCommunicable();
		void sendCommunicable(std::string msg);
		void accept(sf::TcpSocket& connected) { satellite->accept(connected); }
	};
}

#endif // !SATELLITERENDER_H
