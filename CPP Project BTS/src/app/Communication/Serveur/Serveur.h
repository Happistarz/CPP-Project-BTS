#pragma once
#ifndef SERVEUR_H
#define SERVEUR_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <future>
#include "../../Helper/LogDisplayer.h"
namespace CORE {
	/// <summary>
	/// Classe Serveur qui gere le serveur de communication
	/// </summary>
	class Serveur {
	private:
		// configuration
		unsigned short port;
		sf::TcpListener server;

		HELPER::LogDisplayer& logdisplayer;
	public:
		/// <summary>
		/// Constructeur de serveur
		/// </summary>
		/// <param name="port"></param>
		/// <param name="logdisplayer"></param>
		Serveur(unsigned short port, HELPER::LogDisplayer& logdisplayer);

		/// <summary>
		/// Destructeur de serveur
		/// </summary>
		~Serveur();

		/// <summary>
		/// Start listening sur le port
		/// </summary>
		/// <returns></returns>
		bool startListening();

		/// <summary>
		/// Accepte une connexion sur le port
		/// </summary>
		/// <param name="socket"></param>
		/// <returns></returns>
		bool accept(sf::TcpSocket& socket);

		/// <summary>
		/// Se deconnecte du serveur
		/// </summary>
		void disconnect();

		/// <summary>
		/// Envoie un message au client
		/// </summary>
		/// <param name="message"></param>
		/// <param name="connected"></param>
		/// <returns></returns>
		bool send(std::string message, sf::TcpSocket& connected);

		/// <summary>
		/// Recoit un message du client
		/// </summary>
		/// <param name="connected"></param>
		/// <returns></returns>
		std::string receive(sf::TcpSocket& connected);

	};
}
#endif // !SERVEUR_H
