#include "Station.h"

namespace METIER {

	Station::Station(std::string ip, int port, HELPER::LogDisplayer& logdisplayer, sf::TcpSocket& connected) : Communicable::Communicable(ip, port, 5000, logdisplayer, connected) {}

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
		return "aaa";
	}

}