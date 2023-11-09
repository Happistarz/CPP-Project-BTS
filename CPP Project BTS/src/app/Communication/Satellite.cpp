#include "Satellite.h"

namespace METIER {

	Satellite::Satellite(std::string ip, int port) : Communicable::Communicable(ip, port) {}

	Satellite::~Satellite() {}

	void Satellite::pingStation(Communicable* station) {
		// envoi le message
		sendMessage("ping", station->getIp(), station->getPort());
	}

	void Satellite::sendSignal(Communicable* station, std::string message) {
		// envoi le message
		sendMessage(message, station->getIp(), station->getPort());
	}

	std::string Satellite::receiveSignal(Communicable* station) {
		// recoit le message
		return receiveMessage();
	}
}