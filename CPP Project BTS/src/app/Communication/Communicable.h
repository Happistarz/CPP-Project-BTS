#pragma once

#ifndef COMMUNICABLE_H
#define COMMUNICABLE_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <queue>
#include "Client/Client.h"
#include "Serveur/Serveur.h"
#include "../Helper/LogDisplayer.h"

namespace METIER {
	/// <summary>
	/// Classe permettant de communiquer avec un autre objet Communicable
	/// </summary>
	class Communicable {
	private:
		// communication
		CORE::Client* client;
		CORE::Serveur* serveur;

		// thread
		sf::Thread listeningThread;
		std::mutex mutex;
		bool listening;
		void handleConnection();

		// connected
		sf::TcpSocket& connected;
	public:
		/// <summary>
		/// Constructeur
		/// </summary>
		/// <param name="ip"></param>
		/// <param name="listeningPort"></param>
		/// <param name="remotePort"></param>
		/// <param name="logdisplayer"></param>
		/// <param name="connected"></param>
		Communicable(const sf::IpAddress& ip, unsigned short listeningPort, unsigned short remotePort, HELPER::LogDisplayer& logdisplayer, sf::TcpSocket& connected);

		/// <summary>
		/// Destructeur
		/// </summary>
		~Communicable();

		/// <summary>
		/// Start listening thread
		/// </summary>
		void startListeningThread();

		/// <summary>
		/// Stop listening thread
		/// </summary>
		void stopListeningThread();

		/// <summary>
		/// Initialise les objets de communication et les sockets
		/// </summary>
		/// <param name="comm"></param>
		/// <param name="socket"></param>
		void init(Communicable* comm, sf::TcpSocket& socket);

		/// <summary>
		/// Start listening
		/// </summary>
		/// <returns></returns>
		bool startListening();

		/// <summary>
		/// Se connecte a un serveur
		/// </summary>
		/// <returns></returns>
		bool connect();

		/// <summary>
		/// Accepte une connexion
		/// </summary>
		/// <param name="connected"></param>
		/// <returns></returns>
		bool accept(sf::TcpSocket& connected);

		/// <summary>
		/// Deconnecte le socket
		/// </summary>
		void disconnect();

		/// <summary>
		/// Envoie un message
		/// </summary>
		/// <param name="message"></param>
		/// <returns></returns>
		bool sendMessage(std::string message);

		/// <summary>
		/// Recoit un message du serveur
		/// </summary>
		/// <param name="connected"></param>
		/// <returns></returns>
		std::string receiveMessageServer(sf::TcpSocket& connected);

		/// <summary>
		/// Recoit un message du client
		/// </summary>
		/// <returns></returns>
		std::string receiveMessageClient();

		/// <summary>
		/// Get l'ip
		/// </summary>
		/// <returns></returns>
		sf::IpAddress getIp() const { return client->getIp(); }

		/// <summary>
		/// Get le port
		/// </summary>
		/// <returns></returns>
		unsigned short getPort() const { return client->getPort(); }

		/// <summary>
		/// Get le socket du client
		/// </summary>
		/// <returns></returns>
		sf::TcpSocket& getClient() { return client->getClient(); }

		/// <summary>
		/// Get si le socket est connecte
		/// </summary>
		/// <returns></returns>
		bool isConnected() const { return client->isConnected(); }
	};
}


#endif // !COMMUNICABLE_H