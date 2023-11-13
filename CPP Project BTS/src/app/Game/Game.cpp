#include "Game.h"

const unsigned int FPS = 60U;
const sf::VideoMode WINDOW_MODE = sf::VideoMode::getDesktopMode();


namespace APP {
	Game::Game(std::string rootPath, READER::JsonReader* jsonReader) {
		this->rootPath = rootPath;
		this->jsonReader = jsonReader;

		this->window.create(WINDOW_MODE, "Satellite Simulation", sf::Style::None);
		this->window.setFramerateLimit(FPS);
		this->window.setPosition(sf::Vector2i(0, 0));
	}

	Game::~Game() {

	}

	void Game::run() {

		sf::Clock clock;
		float deltaTime = 0.0f;

		GRAPHICS::Simulator* simulator = new GRAPHICS::Simulator(window, rootPath,*jsonReader);
		GRAPHICS::StationRender* stationRender = new GRAPHICS::StationRender(window);
		GRAPHICS::SatelliteRender* satelliteRender = new GRAPHICS::SatelliteRender(window);

		UI::Button* close = new UI::Button(sf::Vector2f(),sf::Vector2f(),"X", 24U, window);

		while (window.isOpen()) {
			sf::Time deltaTimeTimer = clock.restart();
			deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;

			processEvents();
			handleInput();

			// affichage de la fenetre
			window.clear();
			simulator->draw(window);
			stationRender->draw(window);
			satelliteRender->draw(window);
			window.display();
		}
	}

	void Game::processEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// close the window
				window.close();
			}
		}
	}

	void Game::handleInput() {

	}
}