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
		/// <summary>
		/// Constructeur de la classe Station
		/// </summary>
		/// <param name="ip"></param>
		/// <param name="port"></param>
		Station(std::string ip, int port);
		/// <summary>
		/// Destructeur de la classe Station
		/// </summary>
		~Station();

		/// <summary>
		/// Envoi un ping au satellite
		/// </summary>
		/// <param name="satellite"></param>
		void pingSatellite(Communicable& satellite);
		/// <summary>
		/// Envoi un message au satellite
		/// </summary>
		/// <param name="message"></param>
		void sendSignal(std::string message);
		/// <summary>
		/// Recoit un message du satellite
		/// </summary>
		/// <returns></returns>
		std::string receiveSignal();

	};
}


#endif // !STATION_H

