#include "Serveur.h"

namespace CORE {
	Serveur::Serveur(unsigned short port, HELPER::LogDisplayer& logdisplayer) : port(port), logdisplayer(logdisplayer) {}

	Serveur::~Serveur() {
		disconnect();
	}

	bool Serveur::startListening() {
		if (server.listen(port) != sf::Socket::Done) {
			std::cerr << "Error while listening " << port << std::endl;
			logdisplayer.addLine("SERVEUR | Erreur pendant l'�coute");
			return false;
		}

		std::cout << "Listening on " << port << std::endl;
		logdisplayer.addLine("SERVEUR | Ecoute sur le port " + std::to_string(port));
		return true;
	}

	bool Serveur::accept(sf::TcpSocket& connected) {
		// accepte la connexion
		if (server.accept(connected) != sf::Socket::Done) {
			std::cerr << "Error while accepting" << std::endl;
			logdisplayer.addLine("SERVEUR | Erreur pendant l'acceptation");
			return false;
		}

		std::cout << "Connected with " << connected.getRemoteAddress() << ":" << port << std::endl;
		logdisplayer.addLine("SERVEUR | Connexion avec " + connected.getRemoteAddress().toString() + ":" + std::to_string(port));
		return true;
	}

	void Serveur::disconnect() {
		// ferme la socket
		if (server.getLocalPort() != 0) {
			server.close();
		}
	}

	bool Serveur::send(std::string message, sf::TcpSocket& connected) {
		size_t sent;
		if (connected.send(message.c_str(), message.size() + 1, sent) != sf::Socket::Done) {
			std::cerr << "Error while sending" << std::endl;
			logdisplayer.addLine("SERVEUR | Erreur pendant l'envoi");
			return false;
		}
		logdisplayer.addLine("SERVEUR | ENVOI: " + message);
		return true;
	}

	std::string Serveur::receive(sf::TcpSocket& connected) {

		// ------------------------
		// continuer la r�ception
		// le thread est bloqu� ici
		// il faut donc le d�tacher pour qu'il continue � s'ex�cuter en parall�le
		// faire un thread qui attend la r�ception
		// avec un timeout pour �viter de bloquer le thread principal
		// ------------------------


		std::promise<std::string> promise;
		std::future<std::string> future = promise.get_future();

		std::thread([&]() {
			char buffer[2000];
			std::size_t received;

			if (connected.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
				promise.set_value(std::string(buffer, received));
			}
			else {
				promise.set_value("");
			}
			}).detach();

			// Attendez le r�sultat avec un timeout
			std::future_status status = future.wait_for(std::chrono::milliseconds(100));

			if (status == std::future_status::ready) {
				// La r�ception est termin�e dans le d�lai
				return future.get();
			}
			else {
				// Timeout atteint
				return "";
			}
	}
}