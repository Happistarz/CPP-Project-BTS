#include "Communicable.h"

namespace METIER {

	Communicable::Communicable(const sf::IpAddress& ip, unsigned short listeningPort, unsigned short remotePort, HELPER::LogDisplayer& logdisplayer)
		: listening(true)
	{
		serveur = new CORE::Serveur(listeningPort, logdisplayer);
		client = new CORE::Client(ip, remotePort, logdisplayer);

		startListening();
	}

	Communicable::~Communicable() {
		disconnect();

		stopListeningThread();
	}

	void Communicable::startListeningThread(sf::TcpSocket& connected) {
		std::cout << "start listening thread" << std::endl;
		listeningThread = std::thread(&Communicable::handleConnection, this, std::ref(connected));
	}

	void Communicable::stopListeningThread() {
		listening = false;
		if (listeningThread.joinable())
			listeningThread.join();
	}

	void Communicable::handleConnection(sf::TcpSocket& connected) {
		while (listening) {
			std::string message = receiveMessageServer(connected);
			if (!message.empty()) {
				std::cout << message << "aaa"<< std::endl;
				if (message == "ping") {
					sendMessage("pong");
				}
				else {
					sendMessage("received message : " + message);
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	void Communicable::init(Communicable* comm, sf::TcpSocket& socket) {
		comm->connect();
		if (accept(socket)) {
			std::cout << "connected" << std::endl;
			startListeningThread(socket);
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
		client->disconnect();
		serveur->disconnect();
	}

	bool Communicable::sendMessage(std::string message) {
		std::unique_lock<std::mutex> lock(mutex);
		if (!client) return false;
		return client->send(message);
	}

	std::string Communicable::receiveMessageServer(sf::TcpSocket& connected) {
		std::unique_lock<std::mutex> lock(mutex);
		return serveur->receive(connected);
	}

	std::string Communicable::receiveMessageClient() {
		std::unique_lock<std::mutex> lock(mutex);
		return client->receive();
	}
}