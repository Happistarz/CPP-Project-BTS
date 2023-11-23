#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include "../../Helper/LogDisplayer.h"

namespace CORE {
	class Client {
	private:
		sf::IpAddress ip;
		unsigned short remotePort;
		sf::TcpSocket client;

		HELPER::LogDisplayer& logdisplayer;
	public:
		Client(const sf::IpAddress& ip, unsigned short remotePort, HELPER::LogDisplayer& logdisplayer);
		~Client();

		bool connect();
		void disconnect();
		bool send(std::string message);
		std::string receive();
		sf::IpAddress getIp() const { return ip; }
		unsigned short getPort() const { return remotePort; }
		sf::TcpSocket& getClient() { return client; }
		bool isConnected() const { return client.getRemoteAddress() != sf::IpAddress::None; }
	};
}

#endif // !CLIENT_H

