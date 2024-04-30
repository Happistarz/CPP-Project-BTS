#pragma once

#ifndef COMMUNICABLERENDER_H
#define COMMUNICABLERENDER_H

#include <SFML/Graphics.hpp>
#include "../Constants.h"
#include "../../Helper/Functions.h"
#include "../../Communication/Communicable.h"
#include "../../Interface/Button.h"
#include "../../Interface/TextBox.h"
#include "../../Helper/LogDisplayer.h"
#include "Simulator.h"
#include "../../Interface/Modal.h"

namespace GRAPHICS {
	/// <summary>
	/// Classe pour afficher un communicable
	/// </summary>
	class CommunicableRender {
	private:
		// Les formes
		sf::RectangleShape background;
		sf::RectangleShape box;
		UI::Button* ping;
		UI::Button* send;

		// Les textes
		UI::TextBox* connect;
		UI::TextBox* log;
		HELPER::LogDisplayer* logDisplayer;

		// Le communicable
		sf::Text title;
		METIER::Communicable* communicable;
		int port;
		std::string titleString;

		sf::RenderWindow& window;
	public:
		/// <summary>
		/// Constructeur
		/// </summary>
		/// <param name="window"></param>
		/// <param name="font"></param>
		CommunicableRender(sf::RenderWindow& window, std::string title, int portIn, int portOut, sf::TcpSocket& connected);

		/// <summary>
		/// Destructeur
		/// </summary>
		~CommunicableRender();

		/// <summary>
		/// Affiche le communicable
		/// </summary>
		/// <param name="window"></param>
		void draw(sf::RenderWindow& window);

		/// <summary>
		/// Update le communicable
		/// </summary>
		/// <param name="deltaTime"></param>
		void update(float deltaTime, sf::RenderWindow& window);

		void initGUI(sf::Vector2f pos, sf::Font& font, sf::Font& term, sf::TcpSocket& connected, GRAPHICS::Simulator& simulator, UI::Modal& modal);

		/// <summary>
		/// Envoie un message a un objet communicable
		/// </summary>
		/// <param name="msg"></param>
		void sendCommunicable(std::string msg, GRAPHICS::Simulator& simulator);

		/// <summary>
		/// Accepte une connexion sur le communicable
		/// </summary>
		/// <param name="connected"></param>
		void accept(sf::TcpSocket& connected) { communicable->accept(connected); }

		/// <summary>
		/// Connecte le communicable a un autre objet communicable
		/// </summary>
		void connectCommunicable() { communicable->connect(); }

		/// <summary>
		/// Retourne le communicable
		/// </summary>
		/// <returns></returns>
		METIER::Communicable* getCommunicable() { return communicable; }
	};
}

#endif // !SATELLITERENDER_H
