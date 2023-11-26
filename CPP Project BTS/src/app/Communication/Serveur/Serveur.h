#pragma once
#ifndef SERVEUR_H
#define SERVEUR_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <future>
#include "../../Helper/LogDisplayer.h"
namespace CORE {
	class Serveur {
	private:
		unsigned short port;
		sf::TcpListener server;

		HELPER::LogDisplayer& logdisplayer;
	public:
		Serveur(unsigned short port, HELPER::LogDisplayer& logdisplayer);
		~Serveur();

		bool startListening();
		bool accept(sf::TcpSocket& socket);
		void disconnect();
		bool send(std::string message, sf::TcpSocket& connected);
		std::string receive(sf::TcpSocket& connected);

	};
}
#endif // !SERVEUR_H
