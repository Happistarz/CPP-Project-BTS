#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>

namespace CORE {
	class Client {
	private:
		sf::IpAddress ip;
		unsigned short remotePort;
		sf::TcpSocket client;
	public:
		Client(const sf::IpAddress& ip, unsigned short remotePort);
		~Client();

		bool connect();
		void disconnect();
		bool send(std::string message);
		std::string recieve();
		sf::IpAddress getIp() const { return ip; }
		unsigned short getPort() const { return remotePort; }
		sf::TcpSocket& getClient() { return client; }
		bool isConnected() const { return client.getRemoteAddress() != sf::IpAddress::None; }
	};
}

#endif // !CLIENT_H

