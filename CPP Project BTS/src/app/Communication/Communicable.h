#pragma once

#ifndef COMMUNICABLE_H
#define COMMUNICABLE_H

#include <SFML/Network.hpp>
#include <string>

namespace METIER {
	// abstract class of communicable object
	class Communicable {
	protected:
		// ip of the communicable object
		std::string ip;
		// port of the communicable object
		int port;
		// socket of the communicable object
		sf::TcpSocket socket;
	public:
		// constructor
		Communicable(std::string ip, int port);
		// destructor
		~Communicable();
		// send a message to a communicable object
		void sendMessage(std::string message, std::string communicableIp, int communicablePort);
		// receive a message from a communicable object
		std::string receiveMessage();
		// get the ip of the communicable object
		std::string getIp() const { return ip; }
		// get the port of the communicable object
		int getPort() const { return port; }
		// get the socket of the communicable object
		sf::TcpSocket& getSocket() { return socket; }
	};
}


#endif // !COMMUNICABLE_H