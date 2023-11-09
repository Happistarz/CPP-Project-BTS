#include "Station.h"

namespace METIER {

	Station::Station(std::string ip, int port) : Communicable::Communicable(ip, port) {}

	Station::~Station() {}

	void Station::pingSatellite(Communicable* satellite) {
		// envoi le message
		sendMessage("ping", satellite->getIp(), satellite->getPort());
	}

	void Station::sendSignal(Communicable* satellite, std::string message) {
		// envoi le message
		sendMessage(message, satellite->getIp(), satellite->getPort());
	}

	std::string Station::receiveSignal(Communicable* satellite) {
		// recoit le message
		return receiveMessage();
	}

}