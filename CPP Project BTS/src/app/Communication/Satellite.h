#pragma once

#ifndef SATELLITE_H
#define SATELLITE_H

#include <SFML/Network.hpp>
#include <string>
#include "Communicable.h"

namespace METIER {
	class Satellite : public Communicable {
	private:
	public:
		Satellite(std::string ip, int port);
		~Satellite();

		void pingStation(Communicable& station);
		void sendSignal(Communicable& station, std::string message);
		std::string receiveSignal();
	};
}


#endif // !SATELLITE_H


