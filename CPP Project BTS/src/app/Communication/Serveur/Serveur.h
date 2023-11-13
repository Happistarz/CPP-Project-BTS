#pragma once
#ifndef SERVEUR_H
#define SERVEUR_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>

namespace CORE {
	class Serveur {
	private:
		unsigned short port;
		sf::TcpListener server;

	public:
		Serveur(unsigned short port);
		~Serveur();

		bool startListening();
		bool accept(sf::TcpSocket& socket);
		void disconnect();
		bool send(std::string message, sf::TcpSocket& connected);
		std::string recieve(sf::TcpSocket& connected);

	};
}
#endif // !SERVEUR_H
