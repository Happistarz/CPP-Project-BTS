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
	class Communicable {
	private:
		CORE::Client* client;
		CORE::Serveur* serveur;

		std::queue<std::string> messages;
		std::condition_variable cv;
		sf::Thread listeningThread;
		std::mutex mutex;
		bool listening;
		void handleConnection();
		sf::TcpSocket& connected;
	public:
		Communicable(const sf::IpAddress& ip, unsigned short listeningPort, unsigned short remotePort, HELPER::LogDisplayer& logdisplayer, sf::TcpSocket& connected);
		~Communicable();

		void startListeningThread();
		void stopListeningThread();

		void init(Communicable* comm, sf::TcpSocket& socket);
		void processMessage();

		bool startListening();
		bool connect();
		bool accept(sf::TcpSocket& connected);
		void disconnect();
		bool sendMessage(std::string message);
		std::string receiveMessageServer(sf::TcpSocket& connected);
		std::string receiveMessageClient();
		sf::IpAddress getIp() const { return client->getIp(); }
		unsigned short getPort() const { return client->getPort(); }
		sf::TcpSocket& getClient() { return client->getClient(); }
		bool isConnected() const { return client->isConnected(); }
	};
}


#endif // !COMMUNICABLE_H