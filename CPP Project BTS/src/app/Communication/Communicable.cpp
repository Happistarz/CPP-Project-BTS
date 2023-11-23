#include "Communicable.h"

namespace METIER {

	Communicable::Communicable(const sf::IpAddress& ip, unsigned short listeningPort, unsigned short remotePort, HELPER::LogDisplayer& logdisplayer)  {
		serveur = new CORE::Serveur(listeningPort, logdisplayer);
		client = new CORE::Client(ip, remotePort, logdisplayer);

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

	std::string Communicable::receiveMessageServer(sf::TcpSocket& connected) {
		return serveur->receive(connected);
	}

	std::string Communicable::receiveMessageClient() {
		return client->receive();
	}
}