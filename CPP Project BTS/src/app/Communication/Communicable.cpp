#include "Communicable.h"

namespace METIER {

	Communicable::Communicable(const sf::IpAddress& ip, unsigned short listeningPort, unsigned short remotePort, HELPER::LogDisplayer& logdisplayer, sf::TcpSocket& connected)
		: listening(true), listeningThread(&METIER::Communicable::handleConnection, this), mutex(), cv(), connected(connected)
	{
		serveur = new CORE::Serveur(listeningPort, logdisplayer);
		client = new CORE::Client(ip, remotePort, logdisplayer);

		startListening();
	}

	Communicable::~Communicable() {
		disconnect();

		stopListeningThread();
	}

	void Communicable::startListeningThread() {
		std::cout << "start listening thread" << std::endl;
		listeningThread.launch();
	}

	void Communicable::stopListeningThread() {
		listening = false;
		listeningThread.wait();
	}

	void Communicable::handleConnection() {
		while (listening) {
			std::string message = receiveMessageServer(connected);
			if (!message.empty()) {
				std::unique_lock<std::mutex> lock(mutex);
				messages.push(message);
				cv.notify_one();

				processMessage();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
	}

	void Communicable::processMessage() {
		if (listening) {
			std::unique_lock<std::mutex> lock(mutex);
			if (!messages.empty()) {
				std::string message = messages.front();
				messages.pop();
				lock.unlock();
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				std::cout << "message: " << message << std::endl;
			}
			else {
				cv.wait(lock);
			}
		}
	}

	void Communicable::init(Communicable* comm, sf::TcpSocket& socket) {
		comm->connect();
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