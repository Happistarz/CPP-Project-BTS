#include "Client.h"

namespace CORE {
	Client::Client(const sf::IpAddress& ip, unsigned short remotePort, HELPER::LogDisplayer& logdisplayer) : ip(ip), remotePort(remotePort), logdisplayer(logdisplayer) {}

	Client::~Client() {
		disconnect();
	}

	bool Client::connect() {
		if (client.connect(ip, remotePort) != sf::Socket::Done) {
			std::cerr << "Error while connecting to " << ip << ":" << remotePort << std::endl;
			logdisplayer.addLine("CLIENT | Erreur de connexion au serveur " + ip.toString() + ":" + std::to_string(remotePort));
			return false;
		}

		std::cout << "Connected to " << ip << ":" << remotePort << std::endl;
		logdisplayer.addLine("CLIENT | Connecté au serveur " + ip.toString() + ":" + std::to_string(remotePort));
		return true;
	}

	bool Client::send(std::string message) {
		size_t sent;
		if (client.send(message.c_str(), message.size() + 1, sent) != sf::Socket::Done) {
			std::cerr << "Error while sending" << std::endl;
			logdisplayer.addLine("CLIENT | Erreur d'envoi de message");
			return false;
		}
		return true;
	}

	std::string Client::receive() {
		char buffer[2000];
		std::size_t received;
		client.receive(buffer, sizeof(buffer), received);
		logdisplayer.addLine("CLIENT | RECU: " + std::string(buffer, received));
		return std::string(buffer, received);
	}

	void Client::disconnect() {
		client.disconnect();
	}
}