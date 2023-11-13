#pragma once

#ifndef STATION_H
#define STATION_H

#include <SFML/Network.hpp>
#include <string>
#include "Communicable.h"

namespace METIER {

	/// <summary>
	/// Classe Station qui gere la station
	/// Cette classe envoi des signaux aux satellites afin de communiquer
	/// Protocole de communication TCP/IP
	/// </summary>
	class Station : public Communicable {
	private:
	public:
		Station(std::string ip, int port);
		~Station();

		void pingSatellite(Communicable& satellite);
		void sendSignal(Communicable& satellite, std::string message);
		std::string receiveSignal();

	};
}


#endif // !STATION_H

