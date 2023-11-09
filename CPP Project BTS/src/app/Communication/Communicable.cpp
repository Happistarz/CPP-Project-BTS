#include "Communicable.h"

namespace METIER {

	Communicable::Communicable(std::string ip, int port) : ip(ip), port(port) {
		// bind la socket a l'ip et au port
		socket.connect(ip, port);
	}

	Communicable::~Communicable() {
		// ferme la socket
		socket.disconnect();
	}

	void Communicable::sendMessage(std::string message, std::string communicableIp, int communicablePort) {
		// bind la socket a l'ip et au port
		socket.connect(communicableIp, communicablePort);

		// envoi le message
		socket.send(message.c_str(), message.size() + 1);

		// ferme la socket
		socket.disconnect();
	}

	std::string Communicable::receiveMessage() {
		// recoit le message
		char message[2000];
		std::size_t received;
		socket.receive(message, sizeof(message), received);

		// converti le message en string
		std::string recievedMessage(message, received);

		// retourne le message
		return recievedMessage;
	}
}