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

		APP::Event events;

		// initialisation des objets
		sf::Font font;
		font.loadFromFile(rootPath + "data/assets/arial.ttf");
		sf::Font terminal;
		terminal.loadFromFile(rootPath + "data/assets/VT323.ttf");

		// initialisation de la modal
		sf::Vector2f modalSize = sf::Vector2f(600.f, 200.f);
		UI::Modal* modal = new UI::Modal(
			HELPER::getShapePosition(
				sf::Vector2f(),
				static_cast<sf::Vector2f>(window.getSize() / 2u),
				modalSize
			),
			modalSize,
			"Modal",
			font,
			window
		);


		// initialisation des objets de la simulation
		GRAPHICS::Simulator* simulator = new GRAPHICS::Simulator(window, rootPath, *jsonReader);

		// connexion du satellite et de la station
		sf::TcpSocket stationConnected;
		sf::TcpSocket satelliteConnected;

		// init des objets de la station et du satellite
		GRAPHICS::StationRender* stationRender = new GRAPHICS::StationRender(window, font, terminal, stationConnected, *simulator, *modal);
		GRAPHICS::SatelliteRender* satelliteRender = new GRAPHICS::SatelliteRender(window, font, terminal, satelliteConnected, *simulator, *modal);


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

	void Game::runTest() {
		sf::Clock clock;
		float deltaTime = 0.0f;

		APP::Event events;

		bool modalState = false;

		// initialisation des objets
		sf::Font font;
		font.loadFromFile(rootPath + "data/assets/arial.ttf");

		/*UI::TextInput* textInput = new UI::TextInput(
			sf::Vector2f(150.f, 150.f),
			sf::Vector2f(200.f, 50.f),
			font,
			"test",
			24U,
			window
		);*/

		UI::Button* close = new UI::Button(
			sf::Vector2f(0, 0),
			sf::Vector2f(50.f, 50.f),
			"X",
			font,
			24U,
			window,
			[this]() { window.close(); }
		);

		sf::Vector2f modalSize = sf::Vector2f(600.f, 200.f);

		UI::Modal* modal = new UI::Modal(
			HELPER::getShapePosition(
				sf::Vector2f(),
				static_cast<sf::Vector2f>(window.getSize() / 2u),
				modalSize
			),
			modalSize,
			"Modal",
			font,
			window
		);

		UI::Button* modalButton = new UI::Button(
			sf::Vector2f(150.f, 150.f),
			sf::Vector2f(200.f, 50.f),
			"Open modal",
			font,
			24U,
			window,
			[&]() { 
			
				if (modalState) {
					modalState = false;
					modal->closeModal();
				}
				else {
					modalState = true;
					modal->openModal();
				}
			}
		);


		while (window.isOpen()) {
			// calcul du delta time en ms pour les animations et les deplacements
			sf::Time deltaTimeTimer = clock.restart();
			deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;


			// update de la fenetre
			//textInput->update(window);
			close->update(window);

			modalButton->update(window);
			modal->update();

			// gestion des evenements
			events.processEvents(window);

			// affichage de la fenetre
			window.clear();

			//textInput->draw();
			close->draw();

			modalButton->draw();
			modal->draw();

			// affichage du buffer
			window.display();
		}
	}
}