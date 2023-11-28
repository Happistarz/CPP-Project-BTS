#include "Communicable.h"

namespace METIER {

	Communicable::Communicable(const sf::IpAddress& ip, unsigned short listeningPort, unsigned short remotePort, HELPER::LogDisplayer& logdisplayer, sf::TcpSocket& connected)
		// init tout les attributs de la classe
		: listening(true), listeningThread(&METIER::Communicable::handleConnection, this), mutex(), connected(connected)
	{
		// communication
		serveur = new CORE::Serveur(listeningPort, logdisplayer);
		client = new CORE::Client(ip, remotePort, logdisplayer);

		// start listening
		startListening();
	}

	Communicable::~Communicable() {
		// stop listening
		disconnect();

		stopListeningThread();
	}

	void Communicable::startListeningThread() {
		std::cout << "start listening thread" << std::endl;
		// lance le thread
		listeningThread.launch();
	}

	void Communicable::stopListeningThread() {
		listening = false;
		// attend la fin du thread
		listeningThread.wait();
	}

	void Communicable::handleConnection() {
		// boucle infinie
		while (listening) {
			// recupere le message
			std::string message = receiveMessageServer(connected);
			if (!message.empty()) {
				std::unique_lock<std::mutex> lock(mutex);
			}
			// attend 300ms
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
	}

	void Communicable::init(Communicable* comm, sf::TcpSocket& socket) {
		// initialise les objets de communication et les sockets
		comm->connect();
		// accepte une connexion
		if (accept(socket)) {
			std::cout << "connected" << std::endl;
			startListeningThread();
		}
		else {
			std::cout << "not connected" << std::endl;
		}
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
		// deconnecte le socket
		client->disconnect();
		serveur->disconnect();
	}

	bool Communicable::sendMessage(std::string message) {
		// lock le mutex pour eviter les problemes de concurrence et envoie le message
		std::unique_lock<std::mutex> lock(mutex);
		if (!client) return false;
		return client->send(message);
	}

	std::string Communicable::receiveMessageServer(sf::TcpSocket& connected) {
		// lock le mutex pour eviter les problemes de concurrence et recoit le message
		std::unique_lock<std::mutex> lock(mutex);
		return serveur->receive(connected);
	}

	std::string Communicable::receiveMessageClient() {
		// lock le mutex pour eviter les problemes de concurrence et recoit le message
		std::unique_lock<std::mutex> lock(mutex);
		return client->receive();
	}
}