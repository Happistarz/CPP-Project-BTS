#include "Serveur.h"

namespace CORE {
	Serveur::Serveur(unsigned short port) : port(port) {}

	Serveur::~Serveur() {
		disconnect();
	}

	bool Serveur::startListening() {
		if (server.listen(port) != sf::Socket::Done) {
			std::cerr << "Error while listening " << port << std::endl;
			return false;
		}

		std::cout << "Listening on " << port << std::endl;
		return true;
	}

	bool Serveur::accept(sf::TcpSocket& connected) {
		// accepte la connexion
		if (server.accept(connected) != sf::Socket::Done) {
			std::cerr << "Error while accepting" << std::endl;
			return false;
		}

		std::cout << "Connected with " << connected.getRemoteAddress() << ":" << port << std::endl;
		return true;
	}

	void Serveur::disconnect() {
		// ferme la socket
		if (server.getLocalPort() != 0) {
			server.close();
		}
	}

	bool Serveur::send(std::string message, sf::TcpSocket& connected) {
		size_t sent;
		if (connected.send(message.c_str(), message.size() + 1, sent) != sf::Socket::Done) {
			std::cerr << "Error while sending" << std::endl;
			return false;
		}
		return true;
	}

	std::string Serveur::recieve(sf::TcpSocket& connected) {
		char buffer[2000];
		std::size_t received;
		connected.receive(buffer, sizeof(buffer), received);
		return std::string(buffer, received);
	}
}