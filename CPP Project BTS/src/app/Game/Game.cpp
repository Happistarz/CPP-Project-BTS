#include "Game.h"

const unsigned int FPS = 60U;
const sf::VideoMode WINDOW_MODE = sf::VideoMode::getDesktopMode();


namespace APP {
	Game::Game(std::string rootPath, READER::JsonReader* jsonReader) : rootPath(rootPath), jsonReader(jsonReader) {

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

		// initialisation des objets
		sf::Font font;
		font.loadFromFile(rootPath + "data/assets/arial.ttf");
		sf::Font terminal;
		terminal.loadFromFile(rootPath + "data/assets/VT323.ttf");

		// initialisation des objets de la simulation
		GRAPHICS::Simulator* simulator = new GRAPHICS::Simulator(window, rootPath, *jsonReader);

		// connexion du satellite et de la station
		sf::TcpSocket stationConnected;
		sf::TcpSocket satelliteConnected;

		// init des objets de la station et du satellite
		GRAPHICS::StationRender* stationRender = new GRAPHICS::StationRender(window, font, terminal, stationConnected, *simulator);
		GRAPHICS::SatelliteRender* satelliteRender = new GRAPHICS::SatelliteRender(window, font, terminal, satelliteConnected, *simulator);


		// initialisation des sockets
		stationRender->getCommunicable()->init(satelliteRender->getCommunicable(), stationConnected);
		satelliteRender->getCommunicable()->init(stationRender->getCommunicable(), satelliteConnected);


		// initialisation des objets de la fenetre
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

			// gestion des evenements
			processEvents();

			// update de la fenetre
			close->update();
			simulator->update(deltaTime);

			// update de la station et du satellite
			stationRender->update(deltaTime);
			satelliteRender->update(deltaTime);

			// affichage de la fenetre
			window.clear();

			simulator->draw(window);
			stationRender->draw(window);
			satelliteRender->draw(window);
			close->draw();

			// affichage du buffer
			window.display();
		}

		// deconnexion des sockets
		stationRender->getCommunicable()->disconnect();
		stationRender->getCommunicable()->stopListeningThread();

		satelliteRender->getCommunicable()->disconnect();
		satelliteRender->getCommunicable()->stopListeningThread();
	}

	void Game::processEvents() {
		sf::Event event;
		// gestion des evenements
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// close the window
				window.close();
			}
		}
	}
}