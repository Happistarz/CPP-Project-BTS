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
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);


		while (window.isOpen()) {
			processEvents();
			handleInput();
			window.clear();
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