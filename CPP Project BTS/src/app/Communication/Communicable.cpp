#include "Communicable.h"

namespace METIER {

	Communicable::Communicable(const sf::IpAddress& ip, unsigned short listeningPort, unsigned short remotePort) {
		serveur = new CORE::Serveur(listeningPort);
		client = new CORE::Client(ip, remotePort);

		serveur->startListening();
	}

	Communicable::~Communicable() {
		disconnect();
	}

	bool Communicable::startListening() {
		return serveur->startListening();
	}

	bool Communicable::connect() {
		return client->connect();
	}

	bool Communicable::accept(sf::TcpSocket& connected) {
		return serveur->accept(connected);
	}

	void Communicable::disconnect() {
		client->disconnect();
		serveur->disconnect();
	}

	bool Communicable::sendMessage(std::string message) {
		return client->send(message);
	}

	std::string Communicable::receiveMessage(sf::TcpSocket& connected) {
		return serveur->recieve(connected);
	}
}