#include "Client.h"

namespace CORE {
	Client::Client(const sf::IpAddress& ip, unsigned short remotePort) : ip(ip), remotePort(remotePort) {}

	Client::~Client() {
		disconnect();
	}

	bool Client::connect() {
		if (client.connect(ip, remotePort) != sf::Socket::Done) {
			std::cerr << "Error while connecting to " << ip << ":" << remotePort << std::endl;
			return false;
		}

		std::cout << "Connected to " << ip << ":" << remotePort << std::endl;
		return true;
	}

	bool Client::send(std::string message) {
		size_t sent;
		if (client.send(message.c_str(), message.size() + 1, sent) != sf::Socket::Done) {
			std::cerr << "Error while sending" << std::endl;
			return false;
		}
		return true;
	}

	std::string Client::recieve() {
		char buffer[2000];
		std::size_t received;
		client.receive(buffer, sizeof(buffer), received);
		return std::string(buffer, received);
	}

	void Client::disconnect() {
		client.disconnect();
	}
}