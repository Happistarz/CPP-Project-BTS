#include "Station.h"

namespace METIER {

	Station::Station(std::string ip, int port) : Communicable::Communicable(ip, port, 5000) {}

	Station::~Station() {}

	void Station::pingSatellite(Communicable& satellite) {
		// envoi le message
		sendMessage("ping");
	}

	void Station::sendSignal(std::string message) {
		// envoi le message
		sendMessage(message);
	}

	std::string Station::receiveSignal() {
		// recoit le message
		//return receiveMessage();
		return "";
	}

}