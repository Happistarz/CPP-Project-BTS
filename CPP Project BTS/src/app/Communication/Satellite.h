#pragma once

#ifndef SATELLITE_H
#define SATELLITE_H

#include <SFML/Network.hpp>
#include <string>
#include "Communicable.h"
#include "../Helper/LogDisplayer.h"

namespace METIER {
	/// <summary>
	/// Class satellite qui permet de communiquer avec des communicable
	/// </summary>
	class Satellite : public Communicable {
	private:
	public:
		/// <summary>
		/// Constructeur de satellite
		/// </summary>
		/// <param name="ip"></param>
		/// <param name="port"></param>
		/// <param name="logdisplayer"></param>
		Satellite(std::string ip, int port, HELPER::LogDisplayer& logdisplayer);
		/// <summary>
		/// Destructeur par defaut de satellite
		/// </summary>
		~Satellite();

		/// <summary>
		/// Envoie un ping a une station
		/// </summary>
		/// <param name="station"></param>
		void pingStation(Communicable& station);
		/// <summary>
		/// Envoie un message a une station
		/// </summary>
		/// <param name="station"></param>
		/// <param name="message"></param>
		void sendSignal(Communicable& station, std::string message);
		/// <summary>
		/// Recoit un message d'une station
		/// </summary>
		/// <returns></returns>
		std::string receiveSignal();
	};
}


#endif // !SATELLITE_H


