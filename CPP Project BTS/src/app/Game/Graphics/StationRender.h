#pragma once

#ifndef STATIONRENDER_H
#define STATIONRENDER_H

#include <SFML/Graphics.hpp>
#include "../Constants.h"
#include "../../Helper/Functions.h"
#include "../../Helper/LogDisplayer.h"
#include "../../Communication/Communicable.h"
#include "../../Interface/Button.h"
#include "../../Interface/TextBox.h"
#include "Simulator.h"
#include "../../Interface/Modal.h"

namespace GRAPHICS {
	/// <summary>
	/// Affiche la station
	/// </summary>
	class StationRender {
	private:
		// Les formes
		sf::RectangleShape background;
		sf::RectangleShape stationBox;
		UI::Button* ping;
		UI::Button* send;

		// Les textes
		UI::TextBox* connect;
		UI::TextBox* log;
		HELPER::LogDisplayer* logDisplayer;

		// La station
		sf::Text title;
		METIER::Communicable* station;
	public:
		/// <summary>
		/// Constructeur
		/// </summary>
		/// <param name="window"></param>
		/// <param name="font"></param>
		StationRender(sf::RenderWindow& window, sf::Font& font, sf::Font& term, sf::TcpSocket& connected, GRAPHICS::Simulator& simulator, UI::Modal& modal);

		/// <summary>
		/// Destructeur
		/// </summary>
		~StationRender();

		//void startListeningThread() { station->startListeningThread(); }

		/// <summary>
		/// Affiche la station
		/// </summary>
		/// <param name="window"></param>
		void draw(sf::RenderWindow& window);

		/// <summary>
		/// Update la station
		/// </summary>
		/// <param name="deltaTime"></param>
		void update(float deltaTime, sf::RenderWindow& window);

		/// <summary>
		/// Envoie un message a un objet communicable
		/// </summary>
		/// <param name="msg"></param>
		void sendCommunicable(std::string msg, GRAPHICS::Simulator& simulator);

		/// <summary>
		/// Accepte une connexion sur la station
		/// </summary>
		/// <param name="socket"></param>
		void accept(sf::TcpSocket& socket) { station->accept(socket); }

		/// <summary>
		/// Connecte la station a un objet communicable
		/// </summary>
		void connectCommunicable() { station->connect(); }

		/// <summary>
		/// Retourne l'objet communicable
		/// </summary>
		/// <returns></returns>
		METIER::Communicable* getCommunicable() { return station; }
	};
}

#endif // !STATIONRENDER_H

