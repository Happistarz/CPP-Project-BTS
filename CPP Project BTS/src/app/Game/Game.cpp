#include "Game.h"

const unsigned int FPS = 60U;
const sf::VideoMode WINDOW_MODE = sf::VideoMode::getDesktopMode();


namespace APP {
	Game::Game(std::string rootPath) : rootPath(rootPath+"\\data\\assets\\") {

		// creation de la fenetre
		window.create(
			WINDOW_MODE,
			"Satellite Simulation",
			sf::Style::None
		);

		// parametrage de la fenetre
		window.setFramerateLimit(FPS);
		window.setPosition(sf::Vector2i(0, 0));
	}

	Game::~Game() {
		// delete les pointeurs
		//delete jsonReader;
	}

	void Game::run() {

		// initialisation des variables
		sf::Clock clock;
		float deltaTime = 0.0f;

		APP::Event events;

		// initialisation des fonts
		sf::Font font;
		font.loadFromFile(rootPath + "arial.ttf");
		sf::Font terminal;
		terminal.loadFromFile(rootPath + "VT323.ttf");

		// initialisation de la modal
		sf::Vector2f modalSize = sf::Vector2f(600.f, 200.f);
		UI::Modal* modal = new UI::Modal(
			HELPER::getShapePosition(
				sf::Vector2f(),
				static_cast<sf::Vector2f>(window.getSize() / 2u),
				modalSize
			),
			modalSize, 
			"Envoyer un message",
			font,
			window
		);


		// initialisation des objets de la simulation
		GRAPHICS::Simulator* simulator = new GRAPHICS::Simulator(window, rootPath);

		// connexion du satellite et de la station
		sf::TcpSocket stationConnected;
		sf::TcpSocket satelliteConnected;

		// init des objets de la station et du satellite
		GRAPHICS::CommunicableRender* stationRender = new GRAPHICS::CommunicableRender(window, "Station", 6000, 5000, stationConnected);
		GRAPHICS::CommunicableRender* satelliteRender = new GRAPHICS::CommunicableRender(window, "Satellite", 5000, 6000, satelliteConnected);

		stationRender->initGUI(
			sf::Vector2f(window.getSize().x / 1.5, 10.f),
			font,
			terminal,
			satelliteConnected,
			*simulator,
			*modal
		);

		satelliteRender->initGUI(
			sf::Vector2f(window.getSize().x / 1.5, window.getSize().y / 2),
			font,
			terminal,
			stationConnected,
			*simulator,
			*modal
		);

		// initialisation des sockets
		stationRender->getCommunicable()->init(satelliteRender->getCommunicable(), stationConnected);
		satelliteRender->getCommunicable()->init(stationRender->getCommunicable(), satelliteConnected);


		// initialisation du bouton de fermeture de la fenetre
		UI::Button* close = new UI::Button(
			sf::Vector2f(0, 0),
			sf::Vector2f(50.f, 50.f),
			"X",
			font,
			24U,
			window,
			[this]() { window.close(); }
		);


		// lancement de la boucle principale
		while (window.isOpen()) {
			// calcul du delta time en ms pour les animations et les deplacements
			sf::Time deltaTimeTimer = clock.restart();
			deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;

			// update de la fenetre
			close->update(window);
			simulator->update(deltaTime);

			// update de la station et du satellite
			stationRender->update(deltaTime, window);
			satelliteRender->update(deltaTime, window);

			modal->update();

			// gestion des evenements
			events.processEvents(window);

			// affichage de la fenetre
			window.clear();

			simulator->draw(window);
			stationRender->draw(window);
			satelliteRender->draw(window);

			modal->draw();

			close->draw();

			// affichage du buffer
			window.display();
		}

		// deconnexion des sockets
		stationRender->getCommunicable()->disconnect();
		stationRender->getCommunicable()->stopListeningThread();

		satelliteRender->getCommunicable()->disconnect();
		satelliteRender->getCommunicable()->stopListeningThread();

		// delete les pointeurs
		delete simulator;
		delete stationRender;
		delete satelliteRender;
		delete modal;
		delete close;
	}

	void Game::runTest() {
		sf::Clock clock;
		float deltaTime = 0.0f;

		APP::Event events;

		bool modalState = false;

		// initialisation des objets
		sf::Font font;
		font.loadFromFile(rootPath + "arial.ttf");

		UI::TextInput* textInput = new UI::TextInput(
			sf::Vector2f(150.f, 150.f),
			sf::Vector2f(200.f, 50.f),
			font,
			"test...",
			24U,
			window
		);

		UI::Button* close = new UI::Button(
			sf::Vector2f(0, 0),
			sf::Vector2f(50.f, 50.f),
			"X",
			font,
			24U,
			window,
			[this]() { window.close(); }
		);



		while (window.isOpen()) {
			// calcul du delta time en ms pour les animations et les deplacements
			sf::Time deltaTimeTimer = clock.restart();
			deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;


			// update de la fenetre
			textInput->update(window);
			close->update(window);

			//modalButton->update(window);
			//modal->update();

			// gestion des evenements
			events.processEvents(window);

			// affichage de la fenetre
			window.clear();

			textInput->draw();
			close->draw();

			//modalButton->draw();
			//modal->draw();

			// affichage du buffer
			window.display();
		}
	}
}