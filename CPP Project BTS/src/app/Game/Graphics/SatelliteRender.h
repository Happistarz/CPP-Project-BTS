#pragma once

#ifndef SATELLITERENDER_H
#define SATELLITERENDER_H

#include <SFML/Graphics.hpp>
#include "../Constants.h"
#include "../../Helper/Functions.h"
#include "../../Communication/Satellite.h"
#include "../../Interface/Button.h"
#include "../../Interface/TextBox.h"
#include "../../Helper/LogDisplayer.h"

namespace GRAPHICS {
	/// <summary>
	/// Classe pour afficher le satellite
	/// </summary>
	class SatelliteRender {
	private:
		// Les formes
		sf::RectangleShape background;
		sf::RectangleShape satelliteBox;
		UI::Button* ping;
		UI::Button* send;

		// Les textes
		UI::TextBox* connect;
		UI::TextBox* log;
		HELPER::LogDisplayer* logDisplayer;

		// Le satellite
		sf::Text title;
		METIER::Satellite* satellite;
	public:
		/// <summary>
		/// Constructeur
		/// </summary>
		/// <param name="window"></param>
		/// <param name="font"></param>
		SatelliteRender(sf::RenderWindow& window, sf::Font& font, sf::Font& term, sf::TcpSocket& connected);

		/// <summary>
		/// Destructeur
		/// </summary>
		~SatelliteRender();

		//void startListeningThread() { satellite->startListeningThread(); }
		/// <summary>
		/// Affiche le satellite
		/// </summary>
		/// <param name="window"></param>
		void draw(sf::RenderWindow& window);

		/// <summary>
		/// Update le satellite
		/// </summary>
		/// <param name="deltaTime"></param>
		void update(float deltaTime);

		/// <summary>
		/// Ping un objet communicable
		/// </summary>
		void pingCommunicable();

		/// <summary>
		/// Envoie un message a un objet communicable
		/// </summary>
		/// <param name="msg"></param>
		void sendCommunicable(std::string msg);

		/// <summary>
		/// Accepte une connexion sur le satellite
		/// </summary>
		/// <param name="connected"></param>
		void accept(sf::TcpSocket& connected) { satellite->accept(connected); }

		/// <summary>
		/// Connecte le satellite a un objet communicable
		/// </summary>
		void connectCommunicable() { satellite->connect(); }

		/// <summary>
		/// Retourne le communicable
		/// </summary>
		/// <returns></returns>
		METIER::Communicable* getCommunicable() { return satellite; }
	};
}

#endif // !SATELLITERENDER_H
