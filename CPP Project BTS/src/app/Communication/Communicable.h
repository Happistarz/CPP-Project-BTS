#pragma once

#ifndef COMMUNICABLE_H
#define COMMUNICABLE_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include "Client/Client.h"
#include "Serveur/Serveur.h"


namespace METIER {
	class Communicable {
	private:
		CORE::Client* client;
		CORE::Serveur* serveur;
	public:
		Communicable(const sf::IpAddress& ip, unsigned short listeningPort, unsigned short remotePort);
		~Communicable();

		bool startListening();
		bool connect();
		bool accept(sf::TcpSocket& connected);
		void disconnect();
		bool sendMessage(std::string message);
		std::string receiveMessage(sf::TcpSocket& connected);
		sf::IpAddress getIp() const { return client->getIp(); }
		unsigned short getPort() const { return client->getPort(); }
		sf::TcpSocket& getClient() { return client->getClient(); }
		bool isConnected() const { return client->isConnected(); }
	};
}


#endif // !COMMUNICABLE_H