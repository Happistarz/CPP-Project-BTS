#define DEV 0

#if DEV == 2 || DEV == 1
//#include <windows.h>
//#include <thread>
#include <iostream>
#include <iomanip>
#include "app/Communication/Communicable.h"
#include <SFML/Network.hpp>
#else
#include "app/Game/Game.h"
#include "app/Reader/JsonReader.h"
#include "app/Communication/Communicable.h"
#include "app/Helper/LogDisplayer.h"
#endif // DEV

/// <summary>
/// Entrée principale du programme
/// </summary>
/// <returns></returns>
int main() {
	// DEV = 0 : lancement du jeu
	// DEV = 1 : test de la communication
	// DEV = 2 : test thread

#if DEV == 0
	// recupere le chemin du projet pour les fichiers
	std::string rootPath = __FILE__;
	rootPath = rootPath.substr(0, rootPath.find("main.cpp"));



	// initialise le json reader
	READER::JsonReader* jsonReader = new READER::JsonReader(rootPath + "data/json/test.json");

	// lance le jeu
	APP::Game* game = new APP::Game(rootPath, jsonReader);
	game->run();
	//game->runTest();

	// delete les objets
	delete game;
	delete jsonReader;

#elif DEV == 1
	// test

	METIER::Communicable* station = new METIER::Communicable(sf::IpAddress::getLocalAddress(), 6000, 5000);
	METIER::Communicable* satellite = new METIER::Communicable(sf::IpAddress::getLocalAddress(), 5000, 6000);
	satellite->connect();
	sf::TcpSocket connected;
	station->accept(connected);
	station->connect();
	sf::TcpSocket connected2;
	satellite->accept(connected2);

	std::string message = "yo";
	satellite->sendMessage(message);
	std::cout << station->receiveMessage(connected) << std::endl;

	station->sendMessage(message + "2");
	std::cout << satellite->receiveMessage(connected2) << std::endl;

	station->disconnect();
	satellite->disconnect();

	std::cout << "Appuyez sur une touche pour quitter..." << std::endl;
	std::cin.get();

	// connexion entre serveur et client
	// le serveur s'instancie sur ip et port
	// le serveur ecoute sur le port
	// le client s'intancie sur ip et port
	// quand un client se co au serveur, le serveur accepte la connexion
	// le serveur duplique son socket pour garder l'original pour ecouter
	// le nouveau socket est utilise pour communiquer avec le client
	// le client et le serveur peuvent envoyer et recevoir des messages sur leur socket
	// le client et le nouveau serveur peuvent se deconnecter
#else 
	// test thread

	HELPER::LogDisplayer logdisplayer(10, 10);
	METIER::Communicable* station = new METIER::Communicable(sf::IpAddress::getLocalAddress(), 6000, 5000, logdisplayer);
	METIER::Communicable* satellite = new METIER::Communicable(sf::IpAddress::getLocalAddress(), 5000, 6000, logdisplayer);

	sf::TcpSocket stationco;
	satellite->connect();
	if (station->accept(stationco)) {
		station->startListeningThread(stationco);
	}
	sf::TcpSocket satelliteco;
	station->connect();
	if (satellite->accept(satelliteco)) {
		satellite->startListeningThread(satelliteco);
	}

	std::string message = "yo";
	satellite->sendMessage(message);

	station->sendMessage(message + "2");

	station->stopListeningThread();
	satellite->stopListeningThread();

	station->disconnect();
	satellite->disconnect();

	std::cout << "Appuyez sur une touche pour quitter..." << std::endl;
	std::cin.get();

#endif // DEV

	return 0;
}