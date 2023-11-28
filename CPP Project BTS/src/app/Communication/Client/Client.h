#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include "../../Helper/LogDisplayer.h"

namespace CORE {
	/// <summary>
	/// Classe Client qui gere le client de communication
	/// </summary>
	class Client {
	private:
		// configuration
		sf::IpAddress ip;
		unsigned short remotePort;
		sf::TcpSocket client;

		HELPER::LogDisplayer& logdisplayer;
	public:
		/// <summary>
		/// Constructeur de client
		/// </summary>
		/// <param name="ip"></param>
		/// <param name="remotePort"></param>
		/// <param name="logdisplayer"></param>
		Client(const sf::IpAddress& ip, unsigned short remotePort, HELPER::LogDisplayer& logdisplayer);

		/// <summary>
		/// Desctructeur de client
		/// </summary>
		~Client();

		/// <summary>
		/// Connecte le client au serveur
		/// </summary>
		/// <returns></returns>
		bool connect();

		/// <summary>
		/// Deconnecte le client du serveur
		/// </summary>
		void disconnect();

		/// <summary>
		/// Envoie un message au serveur
		/// </summary>
		/// <param name="message"></param>
		/// <returns></returns>
		bool send(std::string message);

		/// <summary>
		/// Recoit un message du serveur
		/// </summary>
		/// <returns></returns>
		std::string receive();

		/// <summary>
		/// Retourne l'ip du serveur
		/// </summary>
		/// <returns></returns>
		sf::IpAddress getIp() const { return ip; }

		/// <summary>
		/// Retourne le port du serveur
		/// </summary>
		/// <returns></returns>
		unsigned short getPort() const { return remotePort; }

		/// <summary>
		/// Retourne le socket du client
		/// </summary>
		/// <returns></returns>
		sf::TcpSocket& getClient() { return client; }

		/// <summary>
		/// Retourne si le client est connecte
		/// </summary>
		/// <returns></returns>
		bool isConnected() const { return client.getRemoteAddress() != sf::IpAddress::None; }
	};
}

#endif // !CLIENT_H

