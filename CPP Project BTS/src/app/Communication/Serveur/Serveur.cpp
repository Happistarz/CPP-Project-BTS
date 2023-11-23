#include "Serveur.h"

namespace CORE {
	Serveur::Serveur(unsigned short port, HELPER::LogDisplayer& logdisplayer) : port(port), logdisplayer(logdisplayer) {}

	Serveur::~Serveur() {
		disconnect();
	}

	bool Serveur::startListening() {
		if (server.listen(port) != sf::Socket::Done) {
			std::cerr << "Error while listening " << port << std::endl;
			logdisplayer.addLine("SERVEUR | Erreur pendant l'�coute");
			return false;
		}

		std::cout << "Listening on " << port << std::endl;
		logdisplayer.addLine("SERVEUR | Ecoute sur le port " + std::to_string(port));
		return true;
	}

	bool Serveur::accept(sf::TcpSocket& connected) {
		// accepte la connexion
		if (server.accept(connected) != sf::Socket::Done) {
			std::cerr << "Error while accepting" << std::endl;
			logdisplayer.addLine("SERVEUR | Erreur pendant l'acceptation");
			return false;
		}

		std::cout << "Connected with " << connected.getRemoteAddress() << ":" << port << std::endl;
		logdisplayer.addLine("SERVEUR | Connexion avec " + connected.getRemoteAddress().toString() + ":" + std::to_string(port));
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
			logdisplayer.addLine("SERVEUR | Erreur pendant l'envoi");
			return false;
		}
		return true;
	}

	std::string Serveur::receive(sf::TcpSocket& connected) {
		char buffer[2000];
		std::size_t received;
		connected.receive(buffer, sizeof(buffer), received);
		logdisplayer.addLine("SERVEUR | RECU: " + std::string(buffer, received));
		return std::string(buffer, received);
	}
}