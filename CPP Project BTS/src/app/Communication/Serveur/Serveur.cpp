#include "Serveur.h"

namespace CORE {
	Serveur::Serveur(unsigned short port, HELPER::LogDisplayer& logdisplayer) : port(port), logdisplayer(logdisplayer) {}

	Serveur::~Serveur() {
		disconnect();
	}

	bool Serveur::startListening() {
		// lance l'écoute
		if (server.listen(port) != sf::Socket::Done) {
			std::cerr << "Error while listening " << port << std::endl;
			logdisplayer.addLine("SERVEUR | Erreur pendant l'écoute");
			return false;
		}

		// affiche un message de succes
		std::cout << "Listening on " << port << std::endl;
		logdisplayer.addLine("SERVEUR | Ecoute sur le port " + std::to_string(port));
		return true;
	}

	bool Serveur::accept(sf::TcpSocket& connected) {
		// tente d'accepter la connexion
		if (server.accept(connected) != sf::Socket::Done) {
			std::cerr << "Error while accepting" << std::endl;
			logdisplayer.addLine("SERVEUR | Erreur pendant l'acceptation");
			return false;
		}

		// affiche un message de succes
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
		// tente d'envoyer le message
		if (connected.send(message.c_str(), message.size() + 1, sent) != sf::Socket::Done) {
			std::cerr << "Error while sending" << std::endl;
			logdisplayer.addLine("SERVEUR | Erreur pendant l'envoi");
			return false;
		}

		// affiche un message de succes
		logdisplayer.addLine("SERVEUR | ENVOI: " + message);
		return true;
	}

	std::string Serveur::receive(sf::TcpSocket& connected) {
		char buffer[2000];
		std::size_t received;

		// tente de recevoir un message
		connected.setBlocking(false);
		sf::Socket::Status status = connected.receive(buffer, sizeof(buffer), received);
		if (status != sf::Socket::Done) {
			//std::cerr << "Error while receiving" << std::endl;

			if (status == sf::Socket::NotReady) {
				return "";
			}
			logdisplayer.addLine("SERVEUR | Erreur pendant la réception");
			return "";
		}

		// affiche un message de succes
		connected.setBlocking(true);
		logdisplayer.addLine("SERVEUR | RECU: " + std::string(buffer, received));
		return std::string(buffer, received);
	}
}