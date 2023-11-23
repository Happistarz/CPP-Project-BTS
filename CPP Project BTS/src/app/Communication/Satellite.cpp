#include "Satellite.h"

namespace METIER {

	Satellite::Satellite(std::string ip, int port, HELPER::LogDisplayer& logdisplayer) : Communicable::Communicable(ip, port, 6000, logdisplayer) {}

	Satellite::~Satellite() {}

	void Satellite::pingStation(Communicable& station) {
		// envoi le message
		sendMessage("ping");
	}

	void Satellite::sendSignal(Communicable& station, std::string message) {
		// envoi le message
		sendMessage(message);
	}

	std::string Satellite::receiveSignal() {
		// recoit le message
		//return receiveMessage();
		return "";
	}
}